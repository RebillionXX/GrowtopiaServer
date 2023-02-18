#pragma once
#include <string>
#include <cstring>
#include <enet/enet.h>

class Peer {
public:
	Peer(ENetPeer* peer);
	Peer();

	bool IsValid() const;
	uint8_t* GetData();
	void SetData(uint8_t* data);

	ENetPeer* Get();
	std::string GetIp() const;
	uint32_t GetIpAsInt() const;
	uint32_t GetConnectId() const;
	uint32_t GetPing() const;
	uint32_t GetIncomingBandwidth() const;
	uint32_t GetOutgoingBandwidth() const;

	void RequestDisconnect();

private:
	ENetPeer* m_pPeer;
};