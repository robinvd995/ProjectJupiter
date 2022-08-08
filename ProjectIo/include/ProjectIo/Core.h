#pragma once

#include "JupiterCore/Log.hpp"

#define JPT_IO_ENABLE_LOGGER

#ifdef JPT_IO_ENABLE_LOGGER
#define JPT_IO_INFO(msg, ...) Jupiter::Io::n_IoLogger->info(msg, __VA_ARGS__)
#define JPT_IO_ERROR(msg, ...) Jupiter::Io::n_IoLogger->error(msg, __VA_ARGS__)
#define JPT_IO_TRACE(msg, ...) Jupiter::Io::n_IoLogger->trace(msg, __VA_ARGS__)
#define JPT_IO_WARN(msg, ...) Jupiter::Io::n_IoLogger->warn(msg, __VA_ARGS__)
#else
#define JPT_IO_INFO(msg, ...)
#define JPT_IO_ERROR(msg, ...)
#define JPT_IO_TRACE(msg, ...)
#define JPT_IO_WARN(msg, ...)
#endif // JPT_IO_ENABLE_LOGGER

#ifdef JPT_TEST
#define JPT_IO_TEST_CLASS(x) friend class x;
#else
#define JPT_IO_TEST_CLASS(x)
#endif // JPT_TEST

#define JPT_IO_MANAGER_CLASS(class_name) \
private: \
class_name(); \
~class_name(); \
class_name(const class_name&) = delete; \
class_name& operator=(const class_name&) = delete; \
inline static class_name* s_Instance = nullptr; \
friend class ProjectIo;



namespace Jupiter::Io {

	inline Jupiter::Logger* n_IoLogger;

	inline void initializeIoLogger(uint64_t flags = 0) {
		n_IoLogger = Jupiter::Logger::createLogger("jpt_io_logger");
		n_IoLogger->enable(flags);
	}

	inline void deleteIoLogger() {
		Jupiter::Logger::deleteLogger(n_IoLogger);
	}

}
