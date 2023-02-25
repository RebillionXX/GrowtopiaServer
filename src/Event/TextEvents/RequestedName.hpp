#pragma once
#include <fmt/core.h>
#include <Event/EventType.hpp>
#include <Packet/TextFunction.hpp>
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
        CAction::Log((ENetPeer*)pAvatar, "`4Oops! `oYour name is including invalid characters, please try again.``");
        pAvatar->RequestDisconnect();
        return;
    }

    pAvatar->PlayerDialog::Send(DIALOG_TYPE_REGISTRATION, TextParse{});
}