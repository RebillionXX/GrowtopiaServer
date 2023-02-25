#pragma once
#include <enet/enet.h>
#include <Utils/TextParse.hpp>
#include <Utils/Wrapper/DialogBuilder.hpp>

enum eDialogTypes {
    DIALOG_TYPE_REGISTRATION
};

class PlayerDialog {
public:
    PlayerDialog();
    PlayerDialog(ENetPeer* peer);
  
private:
    void SendData(int32_t delayMS, DialogBuilder* pData);

public:
    void Send(eDialogTypes eType, TextParse data);
    
private:
    ENetPeer* m_pPeer;
};