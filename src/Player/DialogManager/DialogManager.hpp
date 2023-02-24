#pragma once
#include <enet/enet.h>
#include <Utils/TextParse.hpp>
#include <Utils/Wrapper/DialogBuilder.hpp>

enum eDialogTypes {
    DIALOG_TYPE_REGISTRATION
};

class DialogManager {
public:
    DialogManager();
    DialogManager(ENetPeer* peer);
  
private:
    void SendData(int32_t delayMS, DialogBuilder* pData);

public:
    template <eDialogTypes eType>
    void Send(TextParse data);
    
private:
    ENetPeer* m_pPeer;
};