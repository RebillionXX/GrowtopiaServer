#pragma once
#include <string>
#include <fmt/format.h>
#include <ENetWrapper/ENetWrapper.hpp>
#include <Packet/PacketFactory.hpp>
#include <Utils/TextParse.hpp>

class CAction {
public:
    template <typename... Args>
    static TextParse Log(ENetPeer* peer, std::string format, Args&&... args) {
        TextParse parser{};
        parser.Add("action", "log");
        parser.Add("msg", fmt::vformat(format, fmt::make_format_args(args...)));
        
        ENetWrapper::SendPacket(peer, parser.GetAsString());
        return parser;
    }
    static TextParse PlaySFX(ENetPeer* peer, std::string sound, int32_t delayMS) {
        TextParse parser{};
        parser.Add("action", "play_sfx");
        parser.Add("file", fmt::format("audio/{}.wav", sound));
        parser.Add<int32_t>("delayMS", delayMS);
        
        ENetWrapper::SendPacket(peer, parser.GetAsString());
        return parser;
    }
};