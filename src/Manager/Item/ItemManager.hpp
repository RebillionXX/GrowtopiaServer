#pragma once
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <Manager/Item/ItemInfo.hpp>

class ItemManager {
public:    
    bool Serialize();
    void Encode();
    void Kill();
    
    ItemInfo* GetItem(uint32_t itemId);

    std::vector<ItemInfo*> GetItems();
    size_t GetItemsLoaded();

public:
    ItemManager() = default;
    ~ItemManager() = default;

private:
    uint16_t m_version;
    uint32_t m_itemCount;
    
    std::vector<ItemInfo*> m_items;
};

ItemManager* GetItemManager();