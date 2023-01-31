#include "JupiterCore/JupiterDateTime.h"

#include <sstream>
#include <iomanip>

namespace Jupiter {

	std::string JDateTime::getCurTimeAsStr() {
		auto t = std::time(nullptr);
		auto tm = std::localtime(&t);
		std::stringstream ss;
		ss << std::put_time(tm, "%H:%M:%S");
		return ss.str();
	}

	std::string JDateTime::getCurDateAsStr() {
		auto t = std::time(nullptr);
		auto tm = std::localtime(&t);
		std::stringstream ss;
		ss << std::put_time(tm, "%d-%m-%Y");
		return ss.str();
	}
}