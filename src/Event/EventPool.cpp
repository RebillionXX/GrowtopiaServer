#include <Event/EventPool.hpp>
#include <magic_enum.hpp>
#include <Logger/Logger.hpp>
#include <Server/ServerPool.hpp>
#include <Utils/MiscUtils.hpp>
#include <Event/TextEvents/RequestedName.hpp>

EventPool g_eventPool;
EventPool* GetEventPool() {
    return &g_eventPool;
}

EventList EventPool::GetEvents() const {
    return m_eventData;
}

EventObject* EventPool::GetEventIfExists(const std::string &keyName) {
	auto iterator = m_eventData.find(keyName);

	if (iterator != m_eventData.end())
        return &((*iterator->second));
	return NULL;
}
EventObject* EventPool::GetEvent(const std::string &keyName) {
	EventObject* pData = GetEventIfExists(keyName);

	if (!pData) {
		pData = new EventObject;
		m_eventData[keyName] = pData;
	}
	return pData;
}

void EventPool::AddQueue(const std::string& eventName, EventArguments) {
    EventData data{ eventName, { pAvatar, pServer, eventData, eventParser, pTankData }};
    m_workerQueue.push_back(std::move(data));
}

void EventPool::RegisterEvents() {
    GetEvent("requestedName")->sig_function.connect(&TextEvent::OnRequestedName);

    Logger::Print("{} Initialized, Registered {} Events", fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Event Pool"), m_eventData.size());

	std::thread t(&EventPool::ServicePoll, this);
	this->m_serviceThread = std::move(t);
}

void EventPool::ServicePoll() {
    while (true) {
        if (m_workerQueue.empty())
            continue;
        auto& pairData = m_workerQueue.front();
        std::string                 eventName = pairData.first;
        std::tuple<EventDataType>   tupleData = pairData.second;

        auto* eventFunction = this->GetEventIfExists(eventName);
        if (!eventFunction)
            continue;
        
        std::shared_ptr<Player> pAvatar     = std::get<0>(tupleData);
        std::shared_ptr<Server> pServer     = std::get<1>(tupleData);
        std::string             eventData   = std::get<2>(tupleData);
        TextParse               eventParser = std::get<3>(tupleData);
        TankPacketData*         pTankData   = std::get<4>(tupleData);

        eventFunction->sig_function(pAvatar, pServer, eventData, eventParser, pTankData);

        m_workerQueue.pop_front();
    }
}