#include <iostream>
#include <string>

#include "CommandParser.hpp"
#include "ProjectIo.h"

#include "Properties.h"
#include "PropertyDefinitions.h"
#include "FileDefinitions.h"

#include "JupiterCore/Core.h"
#include "JupiterCore/Formatter.hpp"
#include "JupiterCore/Log.hpp"

inline static void initProjectIoFunc() {
	using namespace Jupiter::Io;

	FileTypeManager::addFileType(FILE_TYPE_PNG, FILE_USAGE_INPUT, { "png" });
	FileTypeManager::addFileType(FILE_TYPE_COLLADA, FILE_USAGE_INPUT, { "collada", "dae" });
	FileTypeManager::addFileType(FILE_TYPE_TEX_RGBA, FILE_USAGE_OUTPUT, { "tex_rgba" });
	FileTypeManager::addFileType(FILE_TYPE_MODEL_STATIC, FILE_USAGE_OUTPUT, { "model_static"});

	// PropertyValueTemplates
	PropertyValueTemplate* pvTextureNearest = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_NEAREST, "nearest");
	PropertyValueTemplate* pvTextureLinear = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_LINEAR, "linear");
	PropertyValueTemplate* pvTextureNearestMipmapNearest = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_NEAREST_MIPMAP_NEAREST, "nearest_mipmap_nearest");
	PropertyValueTemplate* pvTextureLinearMipmapNearest = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_LINEAR_MIPMAP_NEAREST, "linear_mipmap_nearest");
	PropertyValueTemplate* pvTextureNearestMipmapLinear = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_NEAREST_MIPMAP_LINEAR, "nearest_mipmap_linear");
	PropertyValueTemplate* pvTextureLinearMipmapLinear = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_LINEAR_MIPMAP_LINEAR, "linear_mipmap_linear");

	PropertyValueTemplate* pvTextureRepeat = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_REPEAT, "repeat");
	PropertyValueTemplate* pvTextureClampToEdge = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_CLAMP_TO_EDGE, "clamp_to_edge");
	PropertyValueTemplate* pvTextureClampToBorder = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_CLAMP_TO_BORDER, "clamp_to_border");
	PropertyValueTemplate* pvTextureMirroredRepeat = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_MIRRORED_REPEAT, "mirrored_repeat");
	PropertyValueTemplate* pvTextureMirroredClampToEdge = PropertyManager::addPropertyValueTemplate(PV_TEXTURE_MIRRORED_CLAMP_TO_EDGE, "mirrored_clamp_to_edge");

	// PropertyTemplates
	PropertyTemplate* ptTextureMinFilter = PropertyManager::addPropertyTemplate(PI_TEXTURE_MIN_FILTER, "min_filter", { pvTextureNearest, pvTextureLinear, pvTextureNearestMipmapNearest, pvTextureLinearMipmapNearest, pvTextureNearestMipmapLinear, pvTextureLinearMipmapLinear });
	PropertyTemplate* ptTextureMagFilter = PropertyManager::addPropertyTemplate(PI_TEXTURE_MAG_FILTER, "mag_filter", { pvTextureNearest , pvTextureLinear });
	PropertyTemplate* ptTextureWrapS = PropertyManager::addPropertyTemplate(PI_TEXTURE_WRAP_S, "wrap_s", { pvTextureRepeat, pvTextureClampToEdge, pvTextureClampToBorder, pvTextureMirroredRepeat, pvTextureMirroredClampToEdge }) ;
	PropertyTemplate* ptTextureWrapT = PropertyManager::addPropertyTemplate(PI_TEXTURE_WRAP_T, "wrap_t", { pvTextureRepeat, pvTextureClampToEdge, pvTextureClampToBorder, pvTextureMirroredRepeat, pvTextureMirroredClampToEdge });
	PropertyTemplate* ptTextureWrapR = PropertyManager::addPropertyTemplate(PI_TEXTURE_WRAP_R, "wrap_r", { pvTextureRepeat, pvTextureClampToEdge, pvTextureClampToBorder, pvTextureMirroredRepeat, pvTextureMirroredClampToEdge });

	// PropertyGroupTemplates
	PropertyGroupTemplate* pgTexture = PropertyManager::addPropertyGroupTemplate(PG_GROUP_TEXTURE, "texture_properties", { ptTextureMinFilter, ptTextureMagFilter, ptTextureWrapS, ptTextureWrapT, ptTextureWrapR });

	// PropertyContainerTemplates
	//-- PropertyContainerTemplate* pcTexRgba = PropertyManager::addPropertyContainerTemplate(FILE_TYPE_PNG, FILE_TYPE_TEX_RGBA, { pgTexture });

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

	Jupiter::Core::deleteCoreLogger();
}
