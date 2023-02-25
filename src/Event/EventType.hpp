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

#define EVENT(event, eventName)	                                                \
    class eventName ## {                                                        \
    public:                                                                     \
        static void Run(EventArguments);                                        \
        eventName() { GetEventPool()->AddEvent(event, eventName ##::Run); }     \
    } eventName ## _event;                                                      \
    void eventName ##::Run(EventArguments)                                      

#define ACTION_EVENT(event, eventName)	                                                        \
    class eventName ## {                                                                        \
    public:                                                                                     \
        static void Run(EventArguments);                                                        \
        eventName ##() { GetEventPool()->ActionManager::AddEvent(event, eventName ##::Run); }   \
    } eventName ## _actionEvent;                                                                \
    void eventName ##::Run(EventArguments)                                                      \

#define DIALOG_EVENT(event, eventName)	                                                        \
    class eventName ## {                                                                        \
    public:                                                                                     \
        static void Run(EventArguments);                                                        \
        eventName ##() { GetEventPool()->DialogManager::AddEvent(event, eventName ##::Run); }   \
    } eventName ## _dialogEvent;                                                                \
    void eventName ##::Run(EventArguments)                                                      \

typedef std::pair<std::string, std::tuple<EventDataType>>   EventData;
typedef sigslot::signal<EventDataType>                      EventSignal;
