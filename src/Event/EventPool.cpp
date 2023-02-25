#include <Event/EventPool.hpp>
#include <magic_enum.hpp>
#include <Logger/Logger.hpp>
#include <Server/Server.hpp>
#include <Packet/TextFunction.hpp>
#include <Utils/MiscUtils.hpp>

EventPool g_eventPool;
EventPool* GetEventPool() {
    return &g_eventPool;
}

EventPool::EventPool() : ActionManager(), DialogManager() {
}
EventPool::~EventPool() {

}

EventList EventPool::GetEvents() const {
    return m_data;
}

void EventPool::AddEvent(const std::string& keyName, void (&callable)(EventDataType)) {
    EventObject* pData = new EventObject();
    pData->sig_function.connect(callable);
    m_data[keyName] = pData;
}

EventObject* EventPool::GetEventIfExists(const std::string &keyName) {
	auto iterator = m_data.find(keyName);

	if (iterator != m_data.end())
        return &((*iterator->second));
	return NULL;
}
EventObject* EventPool::GetEvent(const std::string &keyName) {
	EventObject* pData = GetEventIfExists(keyName);

	if (!pData) {
		pData = new EventObject();
		m_data[keyName] = pData;
	}
	return pData;
}

void EventPool::AddQueue(const std::string& eventName, EventArguments) {
    EventData data{ eventName, { pAvatar, pServer, eventData, eventParser, pTankData }};
    m_workerQueue.push_back(std::move(data));
}

void EventPool::RegisterEvents() {
	std::thread t(&EventPool::ServicePoll, this);
	m_serviceThread = std::move(t);
}

void EventPool::ServicePoll() {
    while (true) {
        if (m_workerQueue.empty())
            continue;
        auto& pairData = m_workerQueue.front();
        std::string                 eventName = pairData.first;
        std::tuple<EventDataType>   tupleData = pairData.second;

        Player*                 pAvatar     = std::get<0>(tupleData);
        std::shared_ptr<Server> pServer     = std::get<1>(tupleData);
        std::string             eventData   = std::get<2>(tupleData);
        TextParse               eventParser = std::get<3>(tupleData);
        TankPacketData*         pTankData   = std::get<4>(tupleData);

        auto* eventFunction = this->GetEventIfExists(eventName);
        if (!eventFunction) {
            CAction::Log((ENetPeer*)pAvatar, "`oUnhandled Event, eventName(`w{}``) textParse(`w{}``) tankData(`w{}``)``", eventName, eventParser.GetSize(), fmt::ptr(pTankData));
            continue;
        }

        eventFunction->sig_function(pAvatar, pServer, eventData, eventParser, pTankData);

        m_workerQueue.pop_front();
    }
}