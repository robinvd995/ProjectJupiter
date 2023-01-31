#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include "JupiterCore/EventSystem.h"

namespace Jupiter {

	class EventManager {
		MANAGER_CLASS(EventManager);

	public:
		static EventHandler& getEventHandler();

	private:
		EventHandler m_Handler;
	};

}
