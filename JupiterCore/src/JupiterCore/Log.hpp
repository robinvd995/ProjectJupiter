#pragma once

#include <iostream>
#include <utility>
#include <ctime>

#include "Formatter.hpp"
#include "Time.h"

namespace Jupiter {

#define JPT_LOGGER_FLAG_PREFIX			1			// Shows the type of log prefix, ex:[INFO]
#define JPT_LOGGER_FLAG_COLOR			2			// Enables the color codes for the logger
#define JPT_LOGGER_FLAG_TIMESTAMP		4			// Enables the timestamp prefix
#define JPT_LOGGER_FLAG_DATE			8			// Enable the date prefix
#define JPT_LOGGER_FLAG_NAME			16			// Enables the logger name prefix

	class Logger {

	public:
		inline static Logger* createLogger(const std::string& logger_name) {
			return new Logger(logger_name);
		}

		inline static void deleteLogger(Logger* instance) {
			delete instance;
		}

		template<typename ...Args>
		void info(const std::string& msg, Args ...parameters) {
			print(msg, 0, 0,std::forward<Args>(parameters)...);
		}

		template<typename ...Args>
		void error(const std::string& msg, Args ...parameters) {
			print(msg, 1, 1, std::forward<Args>(parameters)...);
		}

		template<typename ...Args>
		void trace(const std::string& msg, Args ...parameters) {
			print(msg, 3, 2, std::forward<Args>(parameters)...);
		}

		template<typename ...Args>
		void warn(const std::string& msg, Args ...parameters) {
			print(msg, 2, 3, std::forward<Args>(parameters)...);
		}

		template<typename ...Args>
		void print(const std::string& msg, uint32_t prefix, uint32_t color, Args ...parameters) {
			std::string str = msg;
			if (m_Flags != 0) str = ": " + str;
			if (m_Flags & JPT_LOGGER_FLAG_PREFIX) str = s_Prefixes[prefix] + str;
			if (m_Flags & JPT_LOGGER_FLAG_NAME) str = "[" + m_LoggerName + "]" + str;
			if (m_Flags & JPT_LOGGER_FLAG_TIMESTAMP) str = "[" + Time::getCurTimeAsStr() + "]" + str;
			if (m_Flags & JPT_LOGGER_FLAG_DATE) str = "[" + Time::getCurDateAsStr() + "]" + str;
			if (m_Flags & JPT_LOGGER_FLAG_COLOR) str = s_ColorCodes[color] + str + s_ColorCodes[0];
			std::cout << m_Formatter->formatString(str, std::forward<Args>(parameters)...) << std::endl;
		}

		void enable(uint32_t flags) { m_Flags |= flags; }

	private:
		Logger() = delete;
		Logger(const std::string& logger_name) :
			m_LoggerName(logger_name)
		{
			m_Formatter = Formatter::createFormatter({ '[', ']', 2 });
		}

		~Logger() {
			Formatter::deleteFormatter(m_Formatter);
		}

	private:
		inline static const std::string s_Prefixes[4] = { "[INFO]", "[ERROR]", "[WARN]", "[TRACE]" };
		inline static const std::string s_ColorCodes[4] = { "\033[0m","\033[31m","\033[32m","\033[33m" };

	private:
		const std::string m_LoggerName;
		uint64_t m_Flags = 0;
		Formatter* m_Formatter = nullptr;
	};

}
