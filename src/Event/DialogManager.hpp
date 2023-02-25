#pragma once
#include <Event/EventObject.hpp>
#include <Event/EventType.hpp>

class DialogManager {
public:
    EventList GetEvents() const;

    void AddEvent(const std::string& keyName, void (&callable)(EventDataType));
	EventObject* GetEventIfExists(const std::string& keyName);
    EventObject* GetEvent(const std::string& keyName);

public:
    DialogManager() = default;
    ~DialogManager() = default;

private:
    EventList m_data;
};