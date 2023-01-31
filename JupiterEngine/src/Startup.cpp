#include "JupiterEngine/JupiterEngineApplication.h"

int main(int argc, char** argv) {
	Jupiter::JupiterEngineApplication* app = Jupiter::createApplication();
	app->initEngine();
	app->run();
	delete app;
}
