#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/TextFunction.hpp>

ACTION_EVENT("dialog_return", OnDialogReturn) {
    if (!eventParser.Contain("dialog_name"))
        return;

    std::string eventName = eventParser.Get("dialog_name", 1);
    auto* eventFunction = GetEventPool()->DialogManager::GetEventIfExists(eventName);

    if (!eventFunction) {
        CAction::Log((ENetPeer*)pAvatar, "`oUnhandled OnAction::OnDialogReturn, eventName(`w{}``)``", eventName);
        return;
    }
    eventFunction->sig_function(pAvatar, pServer, eventData, eventParser, pTankData);
}