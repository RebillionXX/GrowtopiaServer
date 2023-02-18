#pragma once
#include <memory>
#include <unordered_map>
#include <enet/enet.h>
#include <Player/Player.hpp>

class PlayerPool {
public:
    PlayerPool() = default;
    ~PlayerPool();

    std::shared_ptr<Player> NewPlayer(ENetPeer* peer);
    void RemovePlayer(uint32_t connectId);
    std::shared_ptr<Player> GetPlayer(uint32_t connectId);
    
public:
    std::unordered_map<uint32_t, std::shared_ptr<Player>> GetPlayers();
    std::size_t GetActivePlayers() const;

private:
    std::unordered_map<uint32_t, std::shared_ptr<Player>> m_players{};
};