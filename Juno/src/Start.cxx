#include "JupiterEngine/Application.h"

namespace Jupiter {

	class Juno : public Application {

	public:
		Juno() {}
		~Juno() {}

	};

	Application* createApplication() {
		return new Juno();
	}

}

