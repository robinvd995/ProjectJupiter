#pragma once

#include "Log.hpp"

#define JPT_ENABLE_ASSERTS

#ifdef JPT_PLATFORM_WINDOWS

// WINDOWS SPECIFIC DEFINES HERE

#elif JPT_PLATFORM_LINUX

// LINUX SPECIFIC DEFINES HERE

#elif JPT_PLATFORM_MACOS

// MACOS SPECIFIC DEFINES HERE

#else
#error NO TARGET PLATFORM HAS BEEN DEFINED!
#endif // JPT_PLATFORM_WINDOWS

#ifdef JPT_ENABLE_ASSERTS

#define JPT_ASSERT_(x, ...) if(!x) { JPT_ERROR(__VA_ARGS__); __debugbreak(); }
#define JPT_ASSERT_FAIL(...) { JPT_ERROR(__VA_ARGS__); __debugbreak(); } 

#endif

namespace Jupiter::Core {

	inline Jupiter::Logger* n_CoreLogger;

	inline void initializeCoreLogger(uint64_t flags = 0) {
		n_CoreLogger = Jupiter::Logger::createLogger("jpt_core_logger");
		n_CoreLogger->enable(flags);
	}

	inline void deleteCoreLogger() {
		Jupiter::Logger::deleteLogger(n_CoreLogger);
	}
}

#define JPT_INFO(msg, ...) Jupiter::Core::n_CoreLogger->info(msg, __VA_ARGS__)
#define JPT_ERROR(msg, ...) Jupiter::Core::n_CoreLogger->error(msg, __VA_ARGS__)
#define JPT_TRACE(msg, ...) Jupiter::Core::n_CoreLogger->trace(msg, __VA_ARGS__)
#define JPT_WARN(msg, ...) Jupiter::Core::n_CoreLogger->warn(msg, __VA_ARGS__)

// #define JPT_INFO(message) std::cout << "\033[0m[INFO]: " << message << "\033[0m" << std::endl
// #define JPT_ERROR(message) std::cout << "\033[31m[ERROR]: " << message << "\033[0m" << std::endl
// #define JPT_TRACE(message) std::cout << "\033[32m[TRACE]: " << message << "\033[0m" << std::endl
// #define JPT_WARN(message) std::cout << "\033[33m[WARNING]: " << message << "\033[0m" << std::endl
