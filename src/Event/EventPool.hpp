#pragma once
#include <deque>
#include <tuple>
#include <thread>
#include <Event/EventType.hpp>
#include <Event/EventSignal.hpp>

class EventPool {
public:

public:
    void RegisterEvents();
    EventList GetEvents() const;

	EventObject* GetEventIfExists(const std::string &keyName);
    EventObject* GetEvent(const std::string &keyName);

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