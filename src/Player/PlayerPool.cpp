#include <Player/PlayerPool.hpp>

PlayerPool::~PlayerPool() {
    m_players.clear();
}

Player* PlayerPool::NewPlayer(ENetPeer* peer) {
    m_players[peer->connectID] = new Player(peer);
    return m_players[peer->connectID];
}
void PlayerPool::RemovePlayer(uint32_t connectId) {
    delete m_players[connectId];
    m_players.erase(connectId);
}
Player* PlayerPool::GetPlayer(uint32_t connectId) {
    for (auto& [cId, player] : m_players) {
        if (connectId != cId)
            continue;
        return player;
    }
    return nullptr;
}

std::unordered_map<uint32_t, Player*> PlayerPool::GetPlayers() {
    return this->m_players;
}
size_t PlayerPool::GetActivePlayers() const {
    return m_players.size();
}