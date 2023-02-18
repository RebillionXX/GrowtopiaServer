#include <Server/Server.hpp>
#include <chrono>

Server::Server() : ENetServer{} {
    playerPool = std::make_shared<PlayerPool>();
    worldPool = std::make_shared<WorldPool>();
}
Server::~Server() {
    playerPool.reset();
    worldPool.reset();
}

bool Server::Init(std::string url, uint16_t port, int peerCount) {
    if (!this->ENetServer::Init(port, peerCount))
        return false;
    return true;
}
std::string Server::GetUptime() const {
    auto time = std::chrono::system_clock::now() - this->clock;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(time).count();
    auto mins = std::chrono::duration_cast<std::chrono::minutes>(time).count() % 60;
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(time).count() % 60;
    auto days = hours / 24;

    if (days > 0)
        return fmt::format("{} days, {} hours, {} mins, {} secs", days, hours, mins, secs);
    else if (hours > 0)
        return fmt::format("{} hours, {} mins, {} secs", hours, mins, secs);
    else if (mins > 0)
        return fmt::format("{} mins, {} secs", mins, secs);
    return fmt::format("{} secs", secs);
}

std::shared_ptr<PlayerPool> Server::GetPlayerPool() {
    return this->playerPool;
}
std::shared_ptr<WorldPool> Server::GetWorldPool() {
    return this->worldPool;
}

size_t Server::GetActivePlayers() const {
    return playerPool->GetActivePlayers();
}
size_t Server::GetActiveWorlds() const {
    return worldPool->GetActiveWorlds();
}