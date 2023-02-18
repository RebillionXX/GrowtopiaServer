#include <Player/PlayerItems.hpp>
#include <Manager/Item/ItemComponent.hpp>
#include <Manager/Item/ItemManager.hpp>

PlayerItems::PlayerItems(ENetPeer* pPeer) : m_pPeer(pPeer) {
    for (auto index = 0; index < NUM_BODY_PARTS; index++)
        m_clothes[index] = ITEM_BLANK;
    m_skinColor = Color(0xB4, 0x8A, 0x78, 0xFF);
    m_gems = 0;

    m_bpSpace = 20;
    this->Add(ITEM_FIST, 1);
    this->Add(ITEM_WRENCH, 1);
}

int32_t PlayerItems::GetGems() const {
    return m_gems;
}
void PlayerItems::SetGems(int32_t vGems) {
    m_gems = vGems;
}

uint16_t& PlayerItems::GetCloth(eClothTypes bodyPart) {
    return m_clothes[bodyPart];
}
std::array<uint16_t, NUM_BODY_PARTS>& PlayerItems::GetClothes() {
    return m_clothes;
}
void PlayerItems::SetCloth(eClothTypes bodyPart, uint16_t itemId) {
    if (static_cast<int32_t>(bodyPart) < ITEM_BLANK || static_cast<int32_t>(bodyPart) > NUM_BODY_PARTS)
        return;
    m_clothes[bodyPart] = itemId;
}

bool PlayerItems::Add(uint16_t itemId, uint8_t count, bool sendPacket) {
    if (count < 1)
        return false;
    if (auto it = m_bpItems.find(itemId); it != m_bpItems.end()) {
        auto pItem = GetItemManager()->GetItem(itemId);
        if (!pItem)
            return false;
        if ((it->second + count) > pItem->m_maxAmount)
            return false;
        it->second += count;
    }
    else {
        if (m_bpItems.size() >= m_bpSpace)
            return false;
        m_bpItems.insert_or_assign(itemId, count);
    }
    /*if (send_packet)
        this->Update(item_id, count, true);*/
    return true;
}