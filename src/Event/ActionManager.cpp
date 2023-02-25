#include <Event/ActionManager.hpp>

EventList ActionManager::GetEvents() const {
    return m_data;
}

void ActionManager::AddEvent(const std::string& keyName, void (&callable)(EventDataType)) {
    EventObject* pData = new EventObject();
    pData->sig_function.connect(callable);
    m_data[keyName] = pData;
}

EventObject* ActionManager::GetEventIfExists(const std::string &keyName) {
	auto iterator = m_data.find(keyName);

	if (iterator != m_data.end())
        return &((*iterator->second));
	return NULL;
}
EventObject* ActionManager::GetEvent(const std::string &keyName) {
	EventObject* pData = GetEventIfExists(keyName);

	if (!pData) {
		pData = new EventObject();
		m_data[keyName] = pData;
	}
	return pData;
}