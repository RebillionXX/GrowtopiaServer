#pragma once
#include <deque>
#include <thread>
#include <sigslot/signal.hpp>
#include <Event/EventObject.hpp>
#include <Event/EventType.hpp>

class EventPool {
public:
    void RegisterEvents();
    EventList GetEvents() const;

    void AddEvent(const std::string& keyName, void (&callable)(EventDataType));
	EventObject* GetEventIfExists(const std::string& keyName);
    EventObject* GetEvent(const std::string& keyName);

    void AddQueue(const std::string& eventName, EventArguments);
    
private:
    void ServicePoll();

public:
    EventPool() = default;
    ~EventPool() = default;

private:
    EventList m_eventData;

    std::thread m_serviceThread;
    std::deque<EventData> m_workerQueue;
};

EventPool* GetEventPool();