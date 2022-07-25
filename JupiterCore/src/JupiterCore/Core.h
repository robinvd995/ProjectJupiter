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
#define JPT_ASSERT(x, ...) if(!x) { JPT_CORE_ERROR(__VA_ARGS__); __debugbreak(); }
#define JPT_ASSERT_FAIL(...) { JPT_CORE_ERROR(__VA_ARGS__); __debugbreak(); } 
#else
#define JPT_ASSERT(x, ...)
#define JPT_ASSERT_FAIL(...)
#endif // JPT_ENABLE_ASSERTS


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

#ifdef JPT_CORE_ENABLE_LOGGER
#define JPT_CORE_INFO(msg, ...) Jupiter::Core::n_CoreLogger->info(msg, __VA_ARGS__)
#define JPT_CORE_ERROR(msg, ...) Jupiter::Core::n_CoreLogger->error(msg, __VA_ARGS__)
#define JPT_CORE_TRACE(msg, ...) Jupiter::Core::n_CoreLogger->trace(msg, __VA_ARGS__)
#define JPT_CORE_WARN(msg, ...) Jupiter::Core::n_CoreLogger->warn(msg, __VA_ARGS__)
#else
#define JPT_CORE_INFO(msg, ...)
#define JPT_CORE_ERROR(msg, ...)
#define JPT_CORE_TRACE(msg, ...)
#define JPT_CORE_WARN(msg, ...)
#endif// JPT_CORE_ENABLE_LOGGER



