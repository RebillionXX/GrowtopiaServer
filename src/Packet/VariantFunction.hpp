#pragma once
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/VariantList.hpp>

class VarList {
public:
    static VariantList OnConsoleMessage(ENetPeer* peer, std::string message, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(message);
        
        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
    static VariantList OnTextOverlay(ENetPeer* peer, std::string message, int32_t delayMS = 0) {
        auto vList = VariantList::Create(__func__, delayMS);
        vList.Insert(message);
        
        ENetWrapper::SendVariantList(peer, vList);
        return vList;
    }
};