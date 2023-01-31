#include "Core/JunoApplication.hpp"

namespace Jupiter {

	JupiterEngineApplication* createApplication() {
		return new Juno::JunoApplication();
	}

}
