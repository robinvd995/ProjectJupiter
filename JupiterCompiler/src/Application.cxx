#include "JupiterCompiler.h"

#include "ShaderCompiler.h"

#include <iostream>

int main(int argc, char* argv[]) {
	Jupiter::Core::initializeCoreLogger(JPT_LOGGER_FLAG_PREFIX | JPT_LOGGER_FLAG_COLOR | JPT_LOGGER_FLAG_TIMESTAMP | JPT_LOGGER_FLAG_DATE);
	Jupiter::JupiterCompiler* compiler = new Jupiter::JupiterCompiler(argc, argv);
	compiler->run();
	delete compiler;
	return 0;
}
