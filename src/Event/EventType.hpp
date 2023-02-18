#pragma once
#include <tuple>

#define EventArguments \
    std::shared_ptr<Player> pAvatar, \
    std::shared_ptr<Server> pServer, \
    std::string eventData, \
    TextParse eventParser, \
    TankPacketData* pTankData
    
#define EventDataType \
    std::shared_ptr<Player>, \
    std::shared_ptr<Server>, \
    std::string, \
    TextParse, \
    TankPacketData*

#define EventData std::pair<std::string, std::tuple<EventDataType>>
