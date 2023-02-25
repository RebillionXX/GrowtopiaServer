#include <Event/DialogManager.hpp>

EventList DialogManager::GetEvents() const {
    return m_data;
}

void DialogManager::AddEvent(const std::string& keyName, void (&callable)(EventDataType)) {
    EventObject* pData = new EventObject();
    pData->sig_function.connect(callable);
    m_data[keyName] = pData;
}

EventObject* DialogManager::GetEventIfExists(const std::string &keyName) {
	auto iterator = m_data.find(keyName);

	if (iterator != m_data.end())
        return &((*iterator->second));
	return NULL;
}
EventObject* DialogManager::GetEvent(const std::string &keyName) {
	EventObject* pData = GetEventIfExists(keyName);

	if (!pData) {
		pData = new EventObject();
		m_data[keyName] = pData;
	}
	return pData;
}