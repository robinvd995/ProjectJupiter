#include "JupiterCore/JupiterTime.h"

#include <chrono>

namespace Jupiter::JTime {

	double JTime::hiresTimeAsSeconds() {
		std::chrono::steady_clock::time_point chronotime = std::chrono::high_resolution_clock::now();
		double timeasdouble = std::chrono::duration_cast<std::chrono::milliseconds>(chronotime.time_since_epoch()).count();
		return timeasdouble / 1000.0;
	}

	double JTime::hiresTimeAsMilliseconds() {
		std::chrono::steady_clock::time_point chronotime = std::chrono::high_resolution_clock::now();
		double timeasdouble = std::chrono::duration_cast<std::chrono::milliseconds>(chronotime.time_since_epoch()).count();
		return timeasdouble;
	}
}