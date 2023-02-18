#pragma once
#include <string>
#include <Utils/BinaryReader.hpp>
#include <Utils/BinaryWriter.hpp>

enum eNetMessageType : int32_t {
    NET_MESSAGE_UNKNOWN,
    NET_MESSAGE_SERVER_HELLO,
    NET_MESSAGE_GENERIC_TEXT,
    NET_MESSAGE_GAME_MESSAGE,
    NET_MESSAGE_GAME_PACKET,
    NET_MESSAGE_ERROR,
    NET_MESSAGE_TRACK,
    NET_MESSAGE_CLIENT_LOG_REQUEST,
    NET_MESSAGE_CLIENT_LOG_RESPONSE
};
enum eNetPacketType : uint8_t {
    NET_GAME_PACKET_STATE,
    NET_GAME_PACKET_CALL_FUNCTION,
    NET_GAME_PACKET_UPDATE_STATUS,
    NET_GAME_PACKET_TILE_CHANGE_REQUEST,
    NET_GAME_PACKET_SEND_MAP_DATA,
    NET_GAME_PACKET_SEND_TILE_UPDATE_DATA,
    NET_GAME_PACKET_SEND_TILE_UPDATE_DATA_MULTIPLE,
    NET_GAME_PACKET_TILE_ACTIVATE_REQUEST,
    NET_GAME_PACKET_TILE_APPLY_DAMAGE,
    NET_GAME_PACKET_SEND_INVENTORY_STATE,
    NET_GAME_PACKET_ITEM_ACTIVATE_REQUEST,
    NET_GAME_PACKET_ITEM_ACTIVATE_OBJECT_REQUEST,
    NET_GAME_PACKET_SEND_TILE_TREE_STATE,
    NET_GAME_PACKET_MODIFY_ITEM_INVENTORY,
    NET_GAME_PACKET_ITEM_CHANGE_OBJECT,
    NET_GAME_PACKET_SEND_LOCK,
    NET_GAME_PACKET_SEND_ITEM_DATABASE_DATA,
    NET_GAME_PACKET_SEND_PARTICLE_EFFECT,
    NET_GAME_PACKET_SET_ICON_STATE,
    NET_GAME_PACKET_ITEM_EFFECT,
    NET_GAME_PACKET_SET_CHARACTER_STATE,
    NET_GAME_PACKET_PING_REPLY,
    NET_GAME_PACKET_PING_REQUEST,
    NET_GAME_PACKET_GOT_PUNCHED,
    NET_GAME_PACKET_APP_CHECK_RESPONSE,
    NET_GAME_PACKET_APP_INTEGRITY_FAIL,
    NET_GAME_PACKET_DISCONNECT,
    NET_GAME_PACKET_BATTLE_JOIN,
    NET_GAME_PACKET_BATTLE_EVENT,
    NET_GAME_PACKET_USE_DOOR,
    NET_GAME_PACKET_SEND_PARENTAL,
    NET_GAME_PACKET_GONE_FISHIN,
    NET_GAME_PACKET_STEAM,
    NET_GAME_PACKET_PET_BATTLE,
    NET_GAME_PACKET_NPC,
    NET_GAME_PACKET_SPECIAL,
    NET_GAME_PACKET_SEND_PARTICLE_EFFECT_V2,
    NET_GAME_PACKET_ACTIVE_ARROW_TO_ITEM,
    NET_GAME_PACKET_SELECT_TILE_INDEX,
    NET_GAME_PACKET_SEND_PLAYER_TRIBUTE_DATA
};

#pragma pack(push, 1)
struct TankPacketData {
    eNetPacketType m_type = eNetPacketType::NET_GAME_PACKET_STATE;

    union {
        uint8_t m_objectType = 0;
        uint8_t m_punchIndex;
        uint8_t m_npcType;
    };
    union {
        uint8_t m_jumpCount;
        uint8_t m_buildRange;
        uint8_t m_npcIndex;
        uint8_t m_lostItemCount;
    };
    union {
        uint8_t m_animationType;
        uint8_t m_punchRange;
        uint8_t m_npcAction;
        uint8_t m_particleIndex;
        uint8_t m_steamEffect;
        uint8_t m_diceResult;
        uint8_t m_gainedItemCount;
        uint8_t m_fruitCount;
    };
    union {
        int32_t m_netId = 0;
        int32_t m_ownerId;
        int32_t m_effectFlagsCheck;
        int32_t m_objectChangeType;
        int32_t m_particleEmitterId;
    };
    union {
        int32_t m_item = 0;
        int32_t m_itemNetId;
        int32_t m_targetNetId;
        int32_t m_pingHash;
        int32_t m_pupilColor;
        int32_t m_tilesLength;
    };

    union {
        uint32_t m_value;
        struct {
            uint32_t bUnused : 1;
            uint32_t bFlying : 1;
            uint32_t bUpdate: 1;
            uint32_t bExtended : 1;
            uint32_t bFacingLeft : 1;
        };
    } m_flags;

    union {
        float m_floatVariable = 0;
        float m_waterSpeed;
        float m_objectCount;
    };
    union {
        int32_t m_mainData = 0;
        int32_t m_pingItem;
        int32_t m_elapsedMs;
        int32_t m_delay;
        int32_t m_tileDamage;
        int32_t m_itemId;
        int32_t m_itemSpeed;
        int32_t m_effectFlags;
        int32_t m_objectId;
        int32_t m_hash;
        int32_t m_verifyPosition;
        int32_t m_clientHackType;
    };
    union {
        float m_vectorX = 0;
        float m_positionX;
        float m_acceleration;
        float m_punchRangeIn;
        int32_t m_particlePositionX;
    };
    union {
        float m_vectorY = 0;
        float m_positionY;
        float m_buildRangeIn;
        float m_punchStrength;
        int32_t m_particlePositionY;
    };
    union {
        float m_vectorX2 = 0;
        float m_positionX2;
        float m_destinationX;
        float m_gravityIn;
        float m_speedOut;
        float m_velocityX;
        float m_particleVariable;
        int m_hackTypePrimary;
    };
    union {
        float m_vectorY2 = 0;
        float m_positionY2;
        float m_destinationY;
        float m_speedIn;
        float m_gravityOut;
        float m_velocityY;
        float m_particleAltId;
        int m_hackTypeSecondary;
    };
    union {
        float m_particleRotation = 0;
        float m_npcVariable;
    };
    union {
        uint32_t m_intX = 0;
        uint32_t m_tilePositionX;
        uint32_t m_itemAltId;
        uint32_t m_hairColor;
    };
    union
    {
        uint32_t m_intY = 0;
        uint32_t m_tilePositionY;
        uint32_t m_itemCount;
        uint32_t m_eyesColor;
        uint32_t m_npcSpeed;
        uint32_t m_particleSizeALt;
    };
    uint32_t m_dataLength = 0;
    /*uint32_t m_data = 0;

    void Pack(BinaryWriter& buffer) {
        buffer.Write<uint8_t>(m_type);
        buffer.Write<uint8_t>(m_punchIndex);
        buffer.Write<uint8_t>(m_buildRange);
        buffer.Write<uint8_t>(m_punchRange);
        buffer.Write<int32_t>(m_netId);
        buffer.Write<int32_t>(m_item);
        buffer.Write<uint32_t>(m_flags.m_value);
        buffer.Write<float>(m_floatVariable);
        buffer.Write<int32_t>(m_delay);
        buffer.Write<float>(m_vectorX);
        buffer.Write<float>(m_vectorY);
        buffer.Write<float>(m_vectorX2);
        buffer.Write<float>(m_vectorY2);
        buffer.Write<float>(m_particleRotation);
        buffer.Write<uint32_t>(m_intX);
        buffer.Write<uint32_t>(m_intY);
        buffer.Write<uint32_t>(m_dataLength);
    }*/
};
#pragma pack(pop)