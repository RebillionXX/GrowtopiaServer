#pragma once
#include <string>
#include <Packet/GameUpdatePacket.hpp>
#include <ENetWrapper/Peer.hpp>

class PacketManager {
public:
	std::string DataToString(uint8_t* data, uint32_t dataLen) {
		std::string ret{};
		ret.resize(dataLen - 1);
		std::memcpy((void*)ret.data(), data, dataLen - 1);
		return ret;
	}
	TankPacketData* DataToTankPacket(uint8_t* data, uint32_t dataLen) {
		TankPacketData* tankPacket = (TankPacketData*)data;
		return tankPacket;
	}
	TankPacketData* DataToTankData(uint8_t* data, uint32_t dataLen) {
		if (dataLen < sizeof(TankPacketData))
            return nullptr;
        TankPacketData* tankData = (TankPacketData*)data;
        if (!tankData->m_flags.bExtended)
			return tankData;
		/*if (dataLen < tankData->dataSize + sizeof(TankPacketData))
			return nullptr;*/
		return tankData;
	}
};