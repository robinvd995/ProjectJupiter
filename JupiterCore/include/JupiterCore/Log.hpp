#pragma once

#include <iostream>
#include <utility>
#include <ctime>

#include "Formatter.hpp"
#include "JupiterDateTime.h"

#define JPT_LOGGER_FLAG_PREFIX          1				// Shows the type of log prefix, ex:[INFO]
#define JPT_LOGGER_FLAG_COLOR           2				// Enables the color codes for the logger
#define JPT_LOGGER_FLAG_TIMESTAMP       4				// Enables the timestamp prefix
#define JPT_LOGGER_FLAG_DATE            8				// Enable the date prefix
#define JPT_LOGGER_FLAG_NAME            16				// Enables the logger name prefix

#define JPT_LOGGER_PREFIX_INFO          R"([INFO])"		// Logger prefix for info
#define JPT_LOGGER_PREFIX_ERROR         R"([ERROR])"	// Logger prefix for error
#define JPT_LOGGER_PREFIX_WARN          R"([WARN])"		// Logger prefix for warnings
#define JPT_LOGGER_PREFIX_TRACE         R"([TRACE])"	// Logger prefix for trace

#define JPT_LOGGER_COLOR_WHITE          "\033[0m"		// Color code for white
#define JPT_LOGGER_COLOR_RED            "\033[31m"		// Color code for red
#define JPT_LOGGER_COLOR_GREEN          "\033[32m"		// Color code for green
#define JPT_LOGGER_COLOR_YELLOW         "\033[33m"		// Color code for yellow

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	class Logger {

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="logger_name"></param>
		/// <returns></returns>
		inline static Logger* createLogger(const std::string& logger_name) {
			return new Logger(logger_name);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="instance"></param>
		inline static void deleteLogger(Logger* instance) {
			delete instance;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void info(const std::string& msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_INFO, JPT_LOGGER_COLOR_WHITE,std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void info(const char* msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_INFO, JPT_LOGGER_COLOR_WHITE, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void error(const std::string& msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_ERROR, JPT_LOGGER_COLOR_RED, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void error(const char* msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_ERROR, JPT_LOGGER_COLOR_RED, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void trace(const std::string& msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_TRACE, JPT_LOGGER_COLOR_GREEN, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void trace(const char* msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_TRACE, JPT_LOGGER_COLOR_GREEN, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void warn(const std::string& msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_WARN, JPT_LOGGER_COLOR_YELLOW, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void warn(const char* msg, Args ...parameters) { print(msg, JPT_LOGGER_PREFIX_WARN, JPT_LOGGER_COLOR_YELLOW, std::forward<Args>(parameters)...); }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="msg"></param>
		/// <param name="prefix"></param>
		/// <param name="color"></param>
		/// <param name="...parameters"></param>
		template<typename ...Args>
		void print(const std::string& msg, const std::string& prefix, const std::string& color, Args ...parameters) {
			std::string str = msg;
			if (m_Flags != 0) str = ": " + str;
			if (m_Flags & JPT_LOGGER_FLAG_PREFIX) str = prefix + str;
			if (m_Flags & JPT_LOGGER_FLAG_NAME) str = "[" + m_LoggerName + "]" + str;
			if (m_Flags & JPT_LOGGER_FLAG_TIMESTAMP) str = "[" + JDateTime::getCurTimeAsStr() + "]" + str;
			if (m_Flags & JPT_LOGGER_FLAG_DATE) str = "[" + JDateTime::getCurDateAsStr() + "]" + str;
			if (m_Flags & JPT_LOGGER_FLAG_COLOR) str = color + str + JPT_LOGGER_COLOR_WHITE;
			std::cout << m_Formatter->formatString(str, std::forward<Args>(parameters)...) << std::endl;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="flags"></param>
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
//		inline static const std::string s_Prefixes[4] = { R"([INFO])", R"([ERROR])", R"([WARN])", R"([TRACE])"};
//		inline static const std::string s_ColorCodes[4] = { "\033[0m","\033[31m","\033[32m","\033[33m" };

	private:
		const std::string m_LoggerName;
		uint64_t m_Flags = 0;
		Formatter* m_Formatter = nullptr;
	};

}
