#include <Player/PlayerPool.hpp>

PlayerPool::~PlayerPool() {
    m_players.clear();
}

std::shared_ptr<Player> PlayerPool::NewPlayer(ENetPeer* peer) {
    m_players[peer->connectID] = std::make_shared<Player>(peer);
    return m_players[peer->connectID];
}
void PlayerPool::RemovePlayer(uint32_t connectId) {
    m_players[connectId].reset();
    m_players.erase(connectId);
}
std::shared_ptr<Player> PlayerPool::GetPlayer(uint32_t connectId) {
    for (auto& [cId, player] : m_players) {
        if (connectId != cId)
            continue;
        return player;
    }
    return nullptr;
}

std::unordered_map<uint32_t, std::shared_ptr<Player>> PlayerPool::GetPlayers() {
    return this->m_players;
}
size_t PlayerPool::GetActivePlayers() const {
    return m_players.size();
}