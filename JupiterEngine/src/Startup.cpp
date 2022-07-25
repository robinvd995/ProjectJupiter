#include "Application.h"

int main(int argc, char** argv) {
	Jupiter::Application* app = Jupiter::createApplication();
	app->run();
	delete app;
}
