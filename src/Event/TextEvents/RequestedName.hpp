#pragma once
#include <regex>
#include <Logger/Logger.hpp>
#include <Event/EventType.hpp>
#include <Server/ServerPool.hpp>
#include <Packet/TextFunction.hpp>
#include <Packet/VariantFunction.hpp>
#include <Utils/MiscUtils.hpp>

namespace TextEvent {
    void OnRequestedName(EventArguments) {
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

        VList::OnConsoleMessage(pAvatar, "VariantList TEST!");
    }
}