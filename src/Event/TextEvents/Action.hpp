#pragma once
#include <Event/EventType.hpp>
#include <Event/EventPool.hpp>
#include <Packet/TextFunction.hpp>

EVENT("action", OnAction) {
    if (!eventParser.Contain("action"))
        return;

    std::string eventName = eventParser.Get("action", 1);
    auto* eventFunction = GetEventPool()->ActionManager::GetEventIfExists(eventName);

    if (!eventFunction) {
        CAction::Log((ENetPeer*)pAvatar, "`oUnhandled TextEvents::OnAction, eventName(`w{}``)``", eventName);
        return;
    }
    eventFunction->sig_function(pAvatar, pServer, eventData, eventParser, pTankData);
}