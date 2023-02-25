#pragma once
#include <tuple>
#include <sigslot/signal.hpp>
#include <Player/Player.hpp>
#include <Server/Server.hpp>
#include <Utils/TextParse.hpp>
#include <Packet/GameUpdatePacket.hpp>
    
#define EventArguments                  \
    Player* pAvatar,                    \
    std::shared_ptr<Server> pServer,    \
    std::string eventData,              \
    TextParse eventParser,              \
    TankPacketData* pTankData           \
    
#define EventDataType                   \
    Player*,                            \
    std::shared_ptr<Server>,            \
    std::string,                        \
    TextParse,                          \
    TankPacketData*                     \

#define EVENT(evName, fname)	                                            \
    class fname ## {                                                        \
    public:                                                                 \
        static void Run(EventArguments);                                    \
        fname ##() { GetEventPool()->AddEvent(evName, fname ##::Run); }     \
    } fname ## _event;                                                      \
    void fname ##::Run(EventArguments)                                      \

#define ACTION_EVENT(evName, fname)	                                                        \
    class fname ## {                                                                        \
    public:                                                                                 \
        static void Run(EventArguments);                                                    \
        fname ##() { GetEventPool()->ActionManager::AddEvent(evName, fname ##::Run); }      \
    } fname ## _event;                                                                      \
    void fname ##::Run(EventArguments)                                                      \

#define DIALOG_EVENT(evName, fname)	                                                        \
    class fname ## {                                                                        \
    public:                                                                                 \
        static void Run(EventArguments);                                                    \
        fname ##() { GetEventPool()->DialogManager::AddEvent(evName, fname ##::Run); }      \
    } fname ## _event;                                                                      \
    void fname ##::Run(EventArguments)                                                      \

typedef std::pair<std::string, std::tuple<EventDataType>>   EventData;
typedef sigslot::signal<EventDataType>                      EventSignal;
