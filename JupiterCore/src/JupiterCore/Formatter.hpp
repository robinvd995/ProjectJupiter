#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

// #define JPT_CORE_FORMATTER_MAX_PARAMETER_INSTANCES 16

namespace Jupiter {

	struct Format {
		const char m_Start;
		const char m_End;
		const unsigned int m_Range;

		Format() = delete;
		Format(const char start, const char end, const char range) :
			m_Start(start), m_End(end), m_Range(range)
		{}
	};

	class Formatter {

	public:
		template<typename ...Ts>
		inline std::string formatString(const std::string& str, Ts ...ts) {
			std::vector<std::string> parameters;
			((addStringToList(parameters, toString(ts))), ...);

			std::stringstream ss;
			int i = 0;
			int charsToSkip = 0;
			while (i < str.size()) {
				char c = str[i];
				if (c == m_Format.m_Start) {
					int j = 0;
					int end = -1;
					while ((size_t)i + j < str.size() && j <= m_Format.m_Range) {
						char cc = str[(size_t)i + j + 1];
						if (cc == m_Format.m_End) { end = i + j; break; }
						if (!isdigit(cc)) break;
						j++;
					}
					if (end > 0 && j > 0) {
						std::string indexStr = str.substr((size_t)i + 1, j);
						uint32_t index = std::stoi(indexStr);
						if (index >= parameters.size()) return "Error, parameter count";
						charsToSkip += j + 2;
						ss << parameters[index];
					}
				}
				if (charsToSkip <= 0) ss << c;
				else charsToSkip--;
				i++;
			}

			return ss.str();
		}

		inline static Formatter* createFormatter(Format format) {
			return new Formatter(format);
		}

		inline static void deleteFormatter(Formatter* formatter) {
			delete formatter;
		}

	private:
		Formatter() = delete;
		Formatter(Format format) : m_Format(format) { }
		~Formatter() {}

	private:
		Format m_Format = { '[', ']', 2 };

	private:
		inline static void addStringToList(std::vector<std::string>& list, std::string& str) { list.push_back(str); }
		inline static void addStringToList(std::vector<std::string>& list) { }

		inline static std::string toString(long long val) { return std::to_string(val); }
		inline static std::string toString(double val) { return std::to_string(val); }
		inline static std::string toString(float val) { return std::to_string(val); }
		inline static std::string toString(int val) { return std::to_string(val); }
		inline static std::string toString(long val) { return std::to_string(val); }
		inline static std::string toString(long double val) { return std::to_string(val); }
		inline static std::string toString(unsigned long long val) { return std::to_string(val); }
		inline static std::string toString(unsigned int val) { return std::to_string(val); }
		inline static std::string toString(unsigned long val) { return std::to_string(val); }
		inline static std::string toString(const char* val) { return std::string(val); }
		inline static std::string toString(const unsigned char* val) { return std::string((const char*)val); }
		inline static std::string toString(std::string& val) { return val; }
		inline static std::string toString(const std::string& val) { val; }
		inline static std::string toString(bool val) { return val ? "true" : "false"; }
	};
}
