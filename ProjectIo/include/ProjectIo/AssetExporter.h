#pragma once

#include "Assets.h"

namespace Jupiter::Io {

	class AssetExporter {

	public:
		static void exportTexRGBA(LoadedFile source_file);
		static void exportModelStatic(LoadedFile source_file);
		static void exportShader(LoadedFile source_file);
	};

}