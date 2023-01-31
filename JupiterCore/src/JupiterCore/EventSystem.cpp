#include "JupiterCore/EventSystem.h"

namespace Jupiter {

	EventListener::EventListener(uint priority, EventListenerFunc func) :
		m_ListenerPriority(priority), m_ListenerFunc(func) 
	{}

	EventDispatcher::EventDispatcher(int eventSignature) : 
		m_EventSignature(eventSignature) 
	{}

	void EventDispatcher::addListener(uint priority, EventListenerFunc listenerFunc) {
		m_Listeners.push_back({ priority, listenerFunc });
		// TODO implement priority
	}

	void EventDispatcher::removeListener() {
		// TODO
	}

	void EventDispatcher::publishEvent(JEvent* e) {
		std::vector<EventListener>::iterator it;
		for (it = m_Listeners.begin(); it != m_Listeners.end(); it++) {
			it->m_ListenerFunc(e);
			if (e->m_Handled) break;
		}
	}

	EventRegisterEntry::EventRegisterEntry(uint signature) :
		m_EventSignature(signature), m_EventDispatcher(signature) 
	{}

}