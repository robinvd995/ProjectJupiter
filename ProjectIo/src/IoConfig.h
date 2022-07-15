#pragma once

#include <vector>
#include <string>

#include "Properties.h"
#include "FileTypes.h"

//#include "FileTypes.hpp"

#define JPT_IO_ASSET_ID_MAX_LENGTH 64
#define JPT_IO_ASSET_SOURCE_MAX_LENGTH 128

namespace Jupiter::Io {

	enum class IoOutputStructure
	{
		UNDEFINED = 0,		// 0, err 
		INDIVIDUAL = 1,		// all resources have its own output file
		CONTAINER = 2,		// all resources are put into a single container
		SPECIFIED = 3		// all resoures are put into their specified container
	};

	struct IoAsset {
		FileType* m_InputType = nullptr;
		FileType* m_OutputType = nullptr;
		char m_Id[JPT_IO_ASSET_ID_MAX_LENGTH];
		char m_Source[JPT_IO_ASSET_SOURCE_MAX_LENGTH];
		uint32_t m_IdSize = 0, m_SourceSize = 0;
	};

	struct IoConfigSettings {
		IoOutputStructure m_OutputStructure = (IoOutputStructure)0;

		IoConfigSettings() {}
		IoConfigSettings(IoConfigSettings&) = delete;
	};

	struct IoAssets {
		uint64_t m_Amount = 0;
		std::vector<IoAsset> m_AssetBuffer;

		IoAssets() {}
		IoAssets(IoAssets&) = delete;
	};

	struct IoConfig {
		IoConfigSettings m_ConfigSettings;
		IoAssets m_Assets;

		IoConfig() {}
		IoConfig(IoConfig&) = delete;
	};
}
