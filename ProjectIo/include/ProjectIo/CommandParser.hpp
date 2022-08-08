#pragma once

#include <string>
#include <vector>

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	class CommandParser {

	public:
		CommandParser(CommandParser&) = delete;
		CommandParser(int argc, char* argv[]) { for (int i = 0; i < argc; i++) { pushArgumentLine(argv[i]); } }
		~CommandParser() {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="argLine"></param>
		void pushArgumentLine(const std::string& argLine) { m_Arguments.push_back(argLine); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="identifier"></param>
		/// <param name="result"></param>
		/// <returns></returns>
		bool findArgument(const std::string& identifier, std::string& result) { 
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

	private:
		std::vector<std::string> m_Arguments;

// DEBUG FUNCTIONS
//#define JPT_COMMAND_PARSER_DEBUG
#ifdef JPT_COMMAND_PARSER_DEBUG
#include <iostream>
	public:
		void print() { for (std::string s : m_Arguments) std::cout << s << std::endl; }
#endif // JPT_COMMAND_PARSER_DEBUG
	};
}
