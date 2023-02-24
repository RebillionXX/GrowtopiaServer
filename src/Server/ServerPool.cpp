#include <Server/ServerPool.hpp>
#include <magic_enum.hpp>
#include <ENetWrapper/ENetServer.hpp>
#include <config.hpp>
#include <Logger/Logger.hpp>
#include <Event/EventPool.hpp>
#include <Packet/PacketFactory.hpp>
#include <Utils/Utils.hpp>

ServerPool g_serverPool;
ServerPool* GetServerPool() {
    return &g_serverPool;
}

void ServerPool::Start() {
	std::thread t(&ServerPool::ServicePoll, this);
	this->m_serviceThread = std::move(t);
    this->running.store(true);
}
void ServerPool::Stop() {
    this->running.store(false);
}
bool ServerPool::IsRunning() const {
    return this->running.load();
}

std::shared_ptr<Server> ServerPool::StartInstance() {
    uint8_t instanceId = static_cast<uint8_t>(m_servers.size());
    auto tempPort = Configuration::GetBasePort() + this->serverOffset++;   
    auto server{ std::make_shared<Server>() };

    if (!server->Init(Configuration::GetBaseHost(), tempPort, 0xFF)) {
        Logger::Print(EXCEPTION, "Failed to Initialize {}, port {} is busy...", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "ENetServer"), fmt::format(fmt::emphasis::bold | fg(fmt::color::blue_violet), "{}", tempPort));
        return nullptr;
    }
    Logger::Print(INFO, "Starting up {} Instance", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "ENetServer"));
    Logger::Print("InstanceId: {}, Server located at {}", fmt::format(fmt::emphasis::bold | fg(fmt::color::lavender), "{}", instanceId), fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "udp://{}:{}", Configuration::GetBaseHost(), tempPort));
    m_servers.insert_or_assign(instanceId, std::move(server));
    return m_servers[instanceId];
}
bool ServerPool::StopInstance(uint8_t instanceId) {
    if (this->m_servers.find(instanceId) == this->m_servers.end())
        return false;
    Logger::Print(INFO, "Shutting Down InstanceId {}", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "{}", instanceId));
    return this->m_servers.erase(instanceId) > 0;
}

std::unordered_map<uint8_t, std::shared_ptr<Server>> ServerPool::GetServers() {
    return this->m_servers;
}
std::shared_ptr<Server> ServerPool::GetBalancedServer() {
    for (auto [instanceId, server] : m_servers) {
        if (server->GetActivePlayers() > 1)
            continue;
        return server;
    }
    return this->StartInstance();
}

size_t ServerPool::GetActiveServers() const {
    return this->m_servers.size();
}
size_t ServerPool::GetActivePlayers() const {
    size_t ret{ 0 };
    for (auto [instanceId, server] : m_servers)
        ret += server->GetActivePlayers();
    return ret;
}
size_t ServerPool::GetActiveWorlds() const {
    size_t ret{ 0 };
    for (auto [instanceId, server] : m_servers)
        ret += server->GetActiveWorlds();
    return ret;
}

void ServerPool::ServicePoll() {
    while (this->IsRunning()) {
    for (auto& [instanceId, pServer] : this->GetServers()) {
        while (enet_host_check_events(pServer->GetHost(), pServer->GetEvent())) {
            auto event = *pServer->GetEvent();
            auto playerPool = pServer->GetPlayerPool();
            if (!event.peer || !playerPool)
                break;

            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                if (playerPool->GetPlayer(event.peer->connectID))
                    break;
                Player* pAvatar = playerPool->NewPlayer(event.peer);
                pAvatar->OnConnect();
            } break;
            case ENET_EVENT_TYPE_DISCONNECT: {
                Player* pAvatar = playerPool->GetPlayer(event.peer->connectID);
                if (!pAvatar)
                    break;
                pAvatar->OnDisconnect();
                playerPool->RemovePlayer(event.peer->connectID);
            } break;
            case ENET_EVENT_TYPE_RECEIVE: {
                Player* pAvatar = playerPool->GetPlayer(event.peer->connectID);
                if (event.packet->dataLength < sizeof(IPacketType::m_packetType) + 1 || event.packet->dataLength > 0x400 || !pAvatar) {
                    enet_packet_destroy(event.packet);
                    break;
                }
                auto messageType = *(int32_t*)event.packet->data;
                switch (messageType) {
                case NET_MESSAGE_GENERIC_TEXT:
                case NET_MESSAGE_GAME_MESSAGE: {
                    auto data = this->DataToString(event.packet->data + sizeof(IPacketType::m_packetType), event.packet->dataLength - sizeof(IPacketType::m_packetType));
                    GetEventPool()->AddQueue(data.substr(0, data.find('|')), pAvatar, pServer, data, TextParse(data), nullptr);
                } break;
                default:
                    break;
                }
            } break;
            default:
                break;
            }
        }
        enet_host_service(pServer->GetHost(), nullptr, 1);
    }
    }
}