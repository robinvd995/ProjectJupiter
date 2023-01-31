#include "JupiterEngine/Events/EventManager.h"

namespace Jupiter {
	MANAGER_CLASS_DEFINITION(EventManager);

	EventHandler& EventManager::getEventHandler() {
		return s_Instance->m_Handler;
	}
}
