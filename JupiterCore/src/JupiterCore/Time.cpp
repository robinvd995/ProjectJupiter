#include "Time.h"

#include <sstream>
#include <iomanip>
#include <ctime>

namespace Jupiter {

	std::string Time::getCurTimeAsStr() {
		auto t = std::time(nullptr);
		auto tm = std::localtime(&t);
		std::stringstream ss;
		ss << std::put_time(tm, "%H:%M:%S");
		return ss.str();
	}

	std::string Time::getCurDateAsStr() {
		auto t = std::time(nullptr);
		auto tm = std::localtime(&t);
		std::stringstream ss;
		ss << std::put_time(tm, "%d-%m-%Y");
		return ss.str();
	}
}