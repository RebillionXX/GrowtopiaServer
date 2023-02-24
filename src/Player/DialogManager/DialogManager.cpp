#include <Player/DialogManager/DialogManager.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Player/Player.hpp>
#include <Logger/Logger.hpp>

DialogManager::DialogManager() {
    m_pPeer = nullptr;
}
DialogManager::DialogManager(ENetPeer* peer) {
    m_pPeer = peer;
}

void DialogManager::SendData(int32_t delayMS, DialogBuilder* pData) {
    auto vList = VariantList::Create("OnDialogRequest", delayMS);
    vList.Insert(pData->Get());
        
    auto vPacket = SVariantPacket(vList);
    ENetWrapper::SendPacket(m_pPeer, vPacket);
}

template <eDialogTypes eType>
void DialogManager::Send(TextParse data) {
    DialogBuilder db();

    switch (eType) {
    default:
        break;
    }

    //this->SendData(data.Get<int32_t>("delayMS", 0, "|"), &db);
    //Logger::Print(INFO, "delayMS as INT -> {}", data.Get<int32_t>("delayMS", 0, "|"));
}