#pragma once

#include "FileTypes.h"

namespace Jupiter::Io {

	class FileLoader {

	public:
		static LoadedFile loadPNG(const std::string& src_file);
		static LoadedFile loadCollada(const std::string& src_file);
		static LoadedFile loadGlsl(const std::string& src_file);
	};
}
