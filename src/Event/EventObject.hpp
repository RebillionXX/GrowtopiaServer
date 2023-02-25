#pragma once
#include <unordered_map>
#include <sigslot/signal.hpp>
#include <Event/EventType.hpp>

class EventObject {
public:
    sigslot::signal<EventDataType> sig_function;
};
typedef std::unordered_map<std::string, EventObject*> EventList;