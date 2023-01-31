#include "JupiterCore/JupiterCommandParser.h"

namespace Jupiter {

	CommandParser::CommandParser(int argc, char** argv, bool skipfirst) {
		int start = skipfirst ? 1 : 0;
		for (int i = start; i < argc; i++) {
			if (i == start)
				setCommand(argv[i]);
			else if (argv[i][0] == '-')
				pushFlag(argv[i]);
			else 
				pushArgumentLine(argv[i]);
		} 
	}

	void CommandParser::pushArgumentLine(const std::string& argLine) { 
		m_Arguments.push_back(argLine); 
	}

	void CommandParser::setCommand(const std::string& command) {
		m_Command =  command;
	}

	void CommandParser::pushFlag(const std::string& flag) {
		m_Flags.push_back(flag.substr(1));
	}

	bool CommandParser::findArgument(const std::string& identifier, std::string& result) const {
		const std::string pattern = identifier + "=";
		const size_t patternLength = pattern.size();
		for (std::string arg : m_Arguments) {
			size_t loc = arg.find(pattern, 0);
			if (loc == std::string::npos) continue;
			result = arg.substr(patternLength);
			return true;
		}

		return false;
	}

	bool CommandParser::hasFlag(const std::string& flag) const {
		for (std::string arg : m_Flags) {
			size_t loc = arg.find(flag, 0);
			if (loc == std::string::npos) continue;
			return true;
		}
		return false;
	}

	const std::string& CommandParser::getCommand() const {
		return m_Command;
	}

	bool CommandParser::hasCommand() const {
		return m_Command.size() > 0;
	}
}
