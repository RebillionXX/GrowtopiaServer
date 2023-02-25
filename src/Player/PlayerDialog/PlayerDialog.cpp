#include <Player/PlayerDialog/PlayerDialog.hpp>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Manager/Item/ItemComponent.hpp>

PlayerDialog::PlayerDialog() {
    m_pPeer = nullptr;
}
PlayerDialog::PlayerDialog(ENetPeer* peer) {
    m_pPeer = peer;
}

void PlayerDialog::SendData(int32_t delayMS, DialogBuilder* pData) {
    auto vList = VariantList::Create("OnDialogRequest", delayMS);
    vList.Insert(pData->Get());
        
    auto vPacket = SVariantPacket(vList);
    ENetWrapper::SendPacket(m_pPeer, vPacket);
}

void PlayerDialog::Send(eDialogTypes eType, TextParse data) {
    DialogBuilder db;

    switch (eType) {
    case DIALOG_TYPE_REGISTRATION: {
        db.SetDefaultColor('o')
            ->AddLabel("`wGet a GrowID!``", LEFT, BIG)
            ->AddSpacer();
        if (data.Contain("extra_message"))
            db.AddTextbox(data.Get("extra_message"))->AddSpacer();
        db.AddTextbox("By choosing a `wGrowID``, you can use a name and password to logon from any device. Your`` name`` will be shown to other players!")
            ->AddTextInput("logon", "Name ", data.Get("logon"), 18)
            ->AddSpacer()
            ->AddTextbox("Your `wpassword`` must contain`` 8 to 18 characters, 1 letter, 1 number`` and`` 1 special character: @#!$^&*.,``")
            ->AddTextInputPassword("password", "Password ", data.Get("password"), 18)
            ->AddTextInputPassword("verify_password", "Password Verify ", data.Get("verify_password"), 18)
            ->AddSpacer()
            ->EndDialog("growid_apply", "Cancel", "`wGet a GrowID``");
    } break;
    default:
        break;
    }

    int32_t delayMS = data.Get("delayMS") == "" ? 0 : data.Get<int32_t>("delayMS");
    this->SendData(delayMS, &db);
}