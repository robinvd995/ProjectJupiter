#include "JupiterEngine/Core/TimeManager.h"

namespace Jupiter {
	MANAGER_CLASS_DEFINITION(TimeManager);
	
	TimeManager::TimeManager(double fixedTimestep, double maxAllowedTimestep, double particleTimestep) :
		m_TimeConstants({1.0 / fixedTimestep, 1.0 / maxAllowedTimestep, 1.0 / particleTimestep})
	{}

}