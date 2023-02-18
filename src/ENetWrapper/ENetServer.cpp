#include <ENetWrapper/ENetServer.hpp>

short ENetServer::IdGenerator = 0;

ENetServer::ENetServer() : m_event{} {
	this->m_pServer = nullptr;
	auto id_tpm = IdGenerator++;
	uint32_t str_len = sizeof(IdGenerator) * 2;
	m_uniqueId.resize(str_len);

	static const char* digits = "0123456789ABCDEF";
	for (uint32_t i = 0; i < str_len; ++i)
		m_uniqueId[i] = digits[(id_tpm >> (i << 2)) & 0x0F];
}
ENetServer::ENetServer(int port, int maxPeers) : ENetServer() { 
    Init(port, maxPeers);
}
ENetServer::~ENetServer() {
	enet_host_destroy(m_pServer);
}

bool ENetServer::Init(uint16_t port, int maxPeers) {
	if (this->m_pServer) 
        return false;

	ENetAddress address {
        .host = ENET_HOST_ANY,
        .port = port
    };
	m_pServer = enet_host_create(&address, maxPeers, 2, 0, 0);
	if (!m_pServer)
        return false;
	m_pServer->checksum = enet_crc32;
	enet_host_compress_with_range_coder(m_pServer);
	return true;
}

ENetHost* ENetServer::GetHost() {
    return this->m_pServer;
}
ENetEvent* ENetServer::GetEvent() {
	return &this->m_event;
}