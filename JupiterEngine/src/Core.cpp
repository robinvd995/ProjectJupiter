#include "Core.h"

namespace Jupiter::Engine {

	//Jupiter::Logger* n_EngineLogger = nullptr;

	void initializeEngineLogger(l_uint flags) {
		n_EngineLogger = Jupiter::Logger::createLogger("JupiterEngine");
		n_EngineLogger->enable(flags);
	}

	void deleteLogger() {
		Jupiter::Logger::deleteLogger(n_EngineLogger);
	}

}