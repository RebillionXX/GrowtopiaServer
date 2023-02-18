#pragma once
#include <string>
#include <ENetWrapper/ENetServer.hpp>
#include <Player/PlayerPool.hpp>
#include <World/WorldPool.hpp>
#include <Utils/TimingClock.hpp>

class Server : public ENetServer {
public:
    Server();
    ~Server();

	bool Init(std::string url, uint16_t port, int peerCount);
    std::string GetUptime() const;

    std::shared_ptr<PlayerPool> GetPlayerPool();
    std::shared_ptr<WorldPool> GetWorldPool();
    
    size_t GetActivePlayers() const;
    size_t GetActiveWorlds() const;
    
private:
    std::shared_ptr<PlayerPool> playerPool;
    std::shared_ptr<WorldPool> worldPool;

    time_point clock        { system_clock::now() };
};

struct ServerData {
    char* serverUrl;
    uint16_t serverPort;
};