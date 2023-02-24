#pragma once
#include <ENetWrapper/ENetWrapper.hpp>
#include <Player/Player.hpp>
#include <Packet/VariantList.hpp>

class VarList {
public:
    static VariantList OnConsoleMessage(Player* pAvatar, std::string message, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(message);
        
        ENetWrapper::SendVariantList(pAvatar, vList);
        return vList;
    }
    static VariantList OnTextOverlay(Player* pAvatar, std::string message, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(message);
        
        ENetWrapper::SendVariantList(pAvatar, vList);
        return vList;
    }
};