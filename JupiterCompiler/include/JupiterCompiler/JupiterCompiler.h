#pragma once

//#define JPT_COMMAND_PARSER_DEBUG

// Core includes
#include "JupiterCore/JupiterCore.h"
#include "JupiterCore/Formatter.hpp"
#include "JupiterCore/Log.hpp"
#include "JupiterCore/JupiterCommandParser.h"

#include <map>

namespace Jupiter {

	typedef void(*CompilerFunc)(const CommandParser& parser);

	class JupiterCompiler {

	public:
		JupiterCompiler() = delete;
		JupiterCompiler(int argc, char* argv[]);
		~JupiterCompiler() = default;

		void run();

	private:
		CommandParser m_CommandParser;
		std::map<const std::string, CompilerFunc> m_FuncMap;
	};
}
