#include "JupiterEngineApplication.h"

int main(int argc, char** argv) {
	Jupiter::JupiterEngineApplication* app = Jupiter::createApplication();
	app->run();
	delete app;
}
