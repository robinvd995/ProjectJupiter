#pragma once

#include <vector>
#include <string>

#include "Properties.h"
#include "FileTypes.h"

#define JPT_IO_CONFIG_ROOT_NODE "io_configuration"
#define JPT_IO_CONFIG_GENERAL_ATTRIB_COUNT "count"

#define JPT_IO_CONFIG_SETTINGS_NODE "settings"
#define JPT_IO_CONFIG_OUTPUT_NODE "output"
#define JPT_IO_CONFIG_OUTPUT_STRUCTURE_ATTRIB "structure"

#define JPT_IO_CONFIG_INCLUDED_ASSETS "included_assets"
#define JPT_IO_CONFIG_ASSET_NODE "asset"
#define JPT_IO_CONFIG_ASSET_ATTRIB_ID "id"
#define JPT_IO_CONFIG_ASSET_ATTRIB_SRC "src"
#define JPT_IO_CONFIG_ASSET_ATTRIB_SRC_TYPE "src_file_type"
#define JPT_IO_CONFIG_ASSET_ATTRIB_TYPE "asset_type"

namespace Jupiter::Io {

	/// <summary>
	/// Enum class defining the different types of output structures
	/// </summary>
	enum class IoOutputStructure {
		UNDEFINED = 0,		// 0, err 
		INDIVIDUAL = 1,		// all resources have its own output file
		CONTAINER = 2,		// all resources are put into a single container
		SPECIFIED = 3		// all resoures are put into their specified container
	};

	struct ProjectIoConfig {
		IoOutputStructure m_OututStructure = IoOutputStructure::UNDEFINED;
		uint32_t m_IncludedAssetCount = 0;
	};

}
