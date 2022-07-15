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

#define JPT_ASSERT(x, ...) if(!x) { JPT_ERROR(__VA_ARGS__); __debugbreak(); }
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

#define JPT_CORE_INFO(msg, ...) Jupiter::Core::n_CoreLogger->info(msg, __VA_ARGS__)
#define JPT_CORE_ERROR(msg, ...) Jupiter::Core::n_CoreLogger->error(msg, __VA_ARGS__)
#define JPT_CORE_TRACE(msg, ...) Jupiter::Core::n_CoreLogger->trace(msg, __VA_ARGS__)
#define JPT_CORE_WARN(msg, ...) Jupiter::Core::n_CoreLogger->warn(msg, __VA_ARGS__)
