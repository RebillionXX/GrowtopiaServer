#include <ENetWrapper/Peer.hpp>
#include <spdlog/fmt/bin_to_hex.h>
#include <Logger/Logger.hpp>

Peer::Peer(ENetPeer* peer) {
	this->m_pPeer = peer;
}
Peer::Peer() {
	this->m_pPeer = nullptr;
}

bool Peer::IsValid() const {
	return this->m_pPeer ? true : false;
}
uint8_t* Peer::GetData() {
	if (!this->IsValid()) 
		return nullptr;
	return (uint8_t*)m_pPeer->data;
}
void Peer::SetData(uint8_t* data) {
	if (!this->IsValid()) 
		return;
	m_pPeer->data = data;
}

ENetPeer* Peer::Get() {
	return this->m_pPeer;
}
std::string Peer::GetIp() const {
	if(!this->IsValid()) 
        return std::string{};
	std::string ret;
	int ipint = m_pPeer->address.host;

	ret += std::to_string(ipint & 0xFF) + ".";
	ret += std::to_string((ipint >>  8) & 0xFF) + ".";
	ret += std::to_string((ipint >> 16) & 0xFF) + ".";
	ret += std::to_string((ipint >> 24) & 0xFF);
	return ret;
}
uint32_t Peer::GetIpAsInt() const {
	if (!this->IsValid())
		return 0;
	return m_pPeer->address.host;
}
uint32_t Peer::GetConnectId() const {
	if (!this->IsValid())
		return 0;
	return m_pPeer->connectID;
}
uint32_t Peer::GetPing() const {
	if (!this->IsValid())
		return 0;
	return m_pPeer->roundTripTime;
}
uint32_t Peer::GetIncomingBandwidth() const {
	if (!this->IsValid())
		return 0;
	return m_pPeer->incomingBandwidth;
}
uint32_t Peer::GetOutgoingBandwidth() const {
	if (!this->IsValid())
		return 0;
	return m_pPeer->outgoingBandwidth;
}

void Peer::RequestDisconnect() {
	enet_peer_disconnect_later(m_pPeer, 0U);
}