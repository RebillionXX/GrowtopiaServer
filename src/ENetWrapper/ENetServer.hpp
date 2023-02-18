#pragma once
#include <thread>
#include <atomic>
#include <enet/enet.h>
#include <ENetWrapper/Peer.hpp>

class ENetServer {
public:
	static short IdGenerator;

protected:
	ENetServer();
	ENetServer(int port, int maxPeers = 256);
	~ENetServer();

	bool Init(uint16_t port, int maxPeers);

public:
	ENetHost* GetHost();
	ENetEvent* GetEvent();

private:
	ENetHost* m_pServer;
	ENetEvent m_event;

	std::string m_uniqueId;
};