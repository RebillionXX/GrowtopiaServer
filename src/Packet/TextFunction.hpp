#pragma once
#include <string>
#include <fmt/format.h>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/PacketFactory.hpp>
#include <Utils/TextParse.hpp>

class CAction {
public:
    template <typename... Args>
    static void Log(Player* pAvatar, std::string format, Args&&... args) {
        TextParse parser{};
        parser.Add("action", "log");
        parser.Add("msg", fmt::vformat(format, fmt::make_format_args(args...)));
        
        ENetWrapper::SendPacket(pAvatar, parser.GetAsString());
    }
};