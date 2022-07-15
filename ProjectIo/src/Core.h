#pragma once

#include "JupiterCore/Log.hpp"

#define JPT_IO_INFO(msg, ...) Jupiter::Io::n_IoLogger->info(msg, __VA_ARGS__)
#define JPT_IO_ERROR(msg, ...) Jupiter::Io::n_IoLogger->error(msg, __VA_ARGS__)
#define JPT_IO_TRACE(msg, ...) Jupiter::Io::n_IoLogger->trace(msg, __VA_ARGS__)
#define JPT_IO_WARN(msg, ...) Jupiter::Io::n_IoLogger->warn(msg, __VA_ARGS__)

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