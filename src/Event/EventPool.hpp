#pragma once
#include <deque>
#include <thread>
#include <Event/EventObject.hpp>
#include <Event/EventType.hpp>
#include <Event/ActionManager.hpp>
#include <Event/DialogManager.hpp>

class EventPool : public ActionManager, public DialogManager {
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
    EventPool();
    ~EventPool();

private:
    EventList m_data;

    std::thread m_serviceThread;
    std::deque<EventData> m_workerQueue;
};

EventPool* GetEventPool();