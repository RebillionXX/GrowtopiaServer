#pragma once
#include <functional>
#include <unordered_map>
#include <sigslot/signal.hpp>
#include <Player/Player.hpp>
#include <Server/Server.hpp>
#include <Packet/GameUpdatePacket.hpp>
#include <Utils/TextParse.hpp>

class EventObject {
public:
    sigslot::signal
    <
        std::shared_ptr<Player>,
        std::shared_ptr<Server>,

        std::string,
        TextParse,
        TankPacketData*
    > sig_function;
};

typedef std::unordered_map<std::string, EventObject*> EventList;