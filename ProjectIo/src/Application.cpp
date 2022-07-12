#include <iostream>
#include <string>

#include "CommandParser.hpp"
#include "ProjectIo.h"

#include "AssetProperties.h"
#include "Properties.h"

#include "JupiterCore/Core.h"
#include "JupiterCore/Formatter.hpp"
#include "JupiterCore/Log.hpp"

inline static void initProjectIoFunc() {
	using namespace Jupiter::Io;

	// Init input file types
	FileTypeManager::addInputFileType((uint32_t)EnumFileInputType::PNG, JPT_IO_FILE_TYPE_INPUT_IDENTIFIER_PNG);
	FileTypeManager::addInputFileType((uint32_t)EnumFileInputType::COLLADA, JPT_IO_FILE_TYPE_INPUT_IDENTIFIER_COLLADA);

	// Init output file types
	FileTypeManager::addOutputFileType((uint32_t)EnumFileOutputType::TEX_RGBA, JPT_IO_FILE_TYPE_OUTPUT_IDENTIFIER_TEX_RGBA);
	FileTypeManager::addOutputFileType((uint32_t)EnumFileOutputType::MODEL_STATIC, JPT_IO_FILE_TYPE_OUTPUT_IDENTIFIER_MODEL_STATIC);

	// Texture property group setup
	AssetPropertyGroup* texturePropertyGroup = AssetPropertyManager::registerPropertyGroup((uint32_t)AssetPropertyGroups::TEXTURE_PROPERTIES, "texture_properties", 5);
	texturePropertyGroup->addProperty(0, (uint32_t)AssetPropertyIdentifiers::TEXTURE_MIN_FILTER, "texture_min_filter");
	texturePropertyGroup->addProperty(1, (uint32_t)AssetPropertyIdentifiers::TEXTURE_MAG_FILTER, "texture_mag_filter");
	texturePropertyGroup->addProperty(2, (uint32_t)AssetPropertyIdentifiers::TEXTURE_WRAP_S, "texture_wrap_s");
	texturePropertyGroup->addProperty(3, (uint32_t)AssetPropertyIdentifiers::TEXTURE_WRAP_T, "texture_wrap_t");
	texturePropertyGroup->addProperty(4, (uint32_t)AssetPropertyIdentifiers::TEXTURE_WRAP_R, "texture_wrap_r");

	// Model property group setup
	AssetPropertyGroup* modelPropertyGroup = AssetPropertyManager::registerPropertyGroup((uint32_t)AssetPropertyGroups::MODEL_PROPERTIES, "model_properties", 1);
	modelPropertyGroup->addProperty(0, 0, "test");

	// Init data transformers
	//DataTransformManager::addDataTransformer((uint32_t)EnumFileInputType::PNG, (uint32_t)EnumFileOutputType::TEX_RGBA, &transformPngToTexRGBA);
	//DataTransformManager::addDataTransformer((uint32_t)EnumFileInputType::COLLADA, (uint32_t)EnumFileOutputType::MODEL_STATIC, &transformColladaToStaticModel);
}

int main(int argc, char* argv[])
{
	Jupiter::Core::initializeCoreLogger(JPT_LOGGER_FLAG_PREFIX | JPT_LOGGER_FLAG_COLOR | JPT_LOGGER_FLAG_TIMESTAMP | JPT_LOGGER_FLAG_DATE/* | JPT_LOGGER_FLAG_NAME*/);

    Jupiter::CommandParser commandParser(argc, argv);
    std::string cfgLocation;
    bool hasConfig = commandParser.findArgument("config", cfgLocation);
    if (!hasConfig) cfgLocation = "Config.io";
	
    Jupiter::Io::ProjectIo projectIo(cfgLocation, initProjectIoFunc);
    projectIo.run();

	//Jupiter::Formatter* formatter = Jupiter::Formatter::createFormatter({'[', ']', 2});
	//std::cout << formatter->formatString("test [0], [1], [2]; end test", 5, false, "something", 879) << std::endl;

	//JPT_INFO("info [0], [1], [2]; end test", 5, false, "something", 879);
	//JPT_ERROR("info [0], [1], [2]; end test", 5, false, "something", 879);
	//JPT_WARN("info [0], [1], [2]; end test", 5, false, "something", 879);
	//JPT_TRACE("info [0], [1], [2]; end test", 5, false, "something", 879);
	//logger->info("info [0], [1], [2]; end test", 5, false, "something", 879);
	//logger->error("error [0], [1], [2]; end test", 5, false, "something", 879);
	//logger->warn("warn [0], [1], [2]; end test", 5, false, "something", 879);
	//logger->trace("trace [0], [1], [2]; end test", 5, false, "something", 879);

	Jupiter::Core::deleteCoreLogger();
}
