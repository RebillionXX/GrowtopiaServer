#pragma once
#include <Event/EventType.hpp>
#include <Player/DialogManager/DialogManager.hpp>
#include <Packet/TextFunction.hpp>
#include <Packet/VariantFunction.hpp>
#include <Utils/TextParse.hpp>
#include <Utils/MiscUtils.hpp>

EVENT("requestedName", OnRequestedName) {
    if (pAvatar->GetDetail().IsFlagOn(CLIENTFLAG_LOGGED_ON))
        return;
    if (!pAvatar->GetDetail().Serialize(eventParser)) {
        pAvatar->RequestDisconnect();
        return;
    }
    pAvatar->SetRawName(pAvatar->GetDetail().GetRequestedName());

    if (!Utils::IsValidUsername(pAvatar->GetRawName()) || (pAvatar->GetRawName().length() < 3 || pAvatar->GetRawName().length() > 10)) {
        CAction::Log(pAvatar, "`4Oops! `oYour name is including invalid characters, please try again.``");
        pAvatar->RequestDisconnect();
        return;
    }

    //pAvatar->Send<DIALOG_TYPE_REGISTRATION>(TextParse{});
}