#pragma once
#if defined(_WIN32) || defined(WIN32)
#pragma comment(lib, "winmm.lib")
#endif

#include <thread>
#include <string>
#include <enet/enet.h>
#include <fmt/core.h>
#include <ENetWrapper/Peer.hpp>
#include <ENetWrapper/ENetServer.hpp>
#include <Packet/PacketFactory.hpp>
#include <Packet/VariantList.hpp>
#include <Player/Player.hpp>

namespace ENetWrapper {  
    inline void SendPacket(ENetPeer* peer, ISPacket& data) {
        if (!peer) 
            return;
        auto packetData = data.m_packetData.data();
        auto dataLength = data.m_packetLength;

        ENetPacket* packet = enet_packet_create(nullptr, 5 + dataLength, ENET_PACKET_FLAG_RELIABLE);
        if (!packet)
            return;

        std::memcpy(packet->data, &data.m_packetType, 4);
        packet->data[dataLength + 4] = 0;

        if ((data.m_packetType != NET_MESSAGE_SERVER_HELLO && dataLength > sizeof(TankPacketData)) ||
            (data.m_packetType == NET_MESSAGE_GAME_MESSAGE))
            std::memcpy(packet->data + 4, packetData, dataLength);

        if (enet_peer_send(peer, 0, packet) != 0)
            enet_packet_destroy(packet);
    }
    inline void SendPacket(ENetPeer* peer, eNetMessageType packetType, const void* pData, uintmax_t dataLength) {
        if (!peer) 
            return;

        ENetPacket* packet = enet_packet_create(nullptr, 5 + dataLength, ENET_PACKET_FLAG_RELIABLE);
        if (!packet)
            return;
            
        std::memcpy(packet->data, &packetType, 4);
        packet->data[dataLength + 4] = 0;
        
        if (pData)
            std::memcpy(packet->data + 4, pData, dataLength);

        if (enet_peer_send(peer, 0, packet) != 0)
            enet_packet_destroy(packet);
    }

    inline void SendPacket(ENetPeer* peer, std::string data) {
        auto vPacket = STextPacket(data);
        ENetWrapper::SendPacket(peer, vPacket);
    }

    inline void SendVariantList(ENetPeer* peer, VariantList vList) {
        auto vPacket = SVariantPacket(vList);
        ENetWrapper::SendPacket(peer, vPacket);
        /*auto memoryAlloc = vList.GetMemoryUsage();
        auto memoryData = vList.Pack();

        TankPacketData* tankPacket = reinterpret_cast<TankPacketData*>(std::malloc(sizeof(TankPacketData) + memoryAlloc));
        tankPacket->m_type = NET_GAME_PACKET_CALL_FUNCTION;
        tankPacket->m_flags.bExtended = true;
        tankPacket->m_netId = vList.netId;
        tankPacket->m_delay = vList.executionDelay;
        tankPacket->m_dataLength = static_cast<uint32_t>(memoryAlloc);
        std::memcpy(reinterpret_cast<uint8_t*>(&tankPacket->m_data), memoryData, memoryAlloc);

        SendPacket(peer, NET_MESSAGE_GAME_PACKET, tankPacket, sizeof(TankPacketData) + tankPacket->m_dataLength); */
    }
}