#pragma once

#pragma once

#include <string>
#include <vector>


namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	class CommandParser {

	public:
		CommandParser() = default;
		CommandParser(CommandParser&) = delete;
		CommandParser(int argc, char** argv, bool skipfirst = true);
		~CommandParser() = default;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="argLine"></param>
		void pushArgumentLine(const std::string& argLine);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="flag"></param>
		void pushFlag(const std::string& flag);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="command"></param>
		void setCommand(const std::string& command);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="identifier"></param>
		/// <param name="result"></param>
		/// <returns></returns>
		bool findArgument(const std::string& identifier, std::string& result) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="flag"></param>
		/// <returns></returns>
		bool hasFlag(const std::string& flag) const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::string& getCommand() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool hasCommand() const;

	private:
		std::vector<std::string> m_Arguments;
		std::vector<std::string> m_Flags;
		std::string m_Command;

		// DEBUG FUNCTIONS
		//#define JPT_COMMAND_PARSER_DEBUG
#ifdef JPT_COMMAND_PARSER_DEBUG
#include <iostream>
	public:
		/// <summary>
		/// Debug function to print all the arguments and flags to the console
		/// </summary>
		void print() { 
			std::cout << "Arguments" << std::endl;
			for (std::string s : m_Arguments) std::cout << s << std::endl;
			std::cout << "Flags" << std::endl;
			for (std::string s : m_Flags) std::cout << s << std::endl;
		}
#endif // JPT_COMMAND_PARSER_DEBUG
	};
}
