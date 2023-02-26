#pragma once
#include <array>
#include <unordered_map>
#include <enet/enet.h>
#include <Manager/Item/ItemType.hpp>
#include <Utils/Color.hpp>

class PlayerItems {
public:
    PlayerItems(ENetPeer* pPeer);
    ~PlayerItems() = default;

public:
    int32_t GetGems() const;
    void SetGems(int32_t gems);

    uint16_t& GetCloth(eClothTypes bodyPart);
    std::array<uint16_t, NUM_BODY_PARTS>& GetClothes();
    void SetCloth(eClothTypes bodyPart, uint16_t itemId);
    
    Color GetSkinColor() const;

    bool AddItem(uint16_t itemId, uint8_t count, bool sendPacket = false);
    
private:
    ENetPeer* m_pPeer;

public:
    int32_t m_gems;
    std::array<uint16_t, NUM_BODY_PARTS> m_clothes;
    Color m_skinColor;

public:
    uint32_t m_backpackSpace;
    std::unordered_map<uint16_t, uint8_t> m_bpItems;
};