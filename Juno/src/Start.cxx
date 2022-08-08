#include "JupiterEngine/JupiterEngineApplication.h"

namespace Jupiter {

	class Juno : public JupiterEngineApplication {

	public:
		Juno() {}
		~Juno() {}

	};

	JupiterEngineApplication* createApplication() {
		return new Juno();
	}

}
