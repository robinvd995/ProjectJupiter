#include <iostream>
#include <string>

#include "CommandParser.hpp"
#include "ProjectIo.h"

#include "Properties.h"
#include "FileTypes.h"
#include "Assets.h"

#include "JupiterCore/Core.h"
#include "JupiterCore/Formatter.hpp"
#include "JupiterCore/Log.hpp"

#define REG_FT(x, ...) FileType* x = FileTypeManager::addFileType(__VA_ARGS__)
#define REG_PV(x, ...) PropertyValueTemplate* x = PropertyManager::addPropertyValueTemplate(__VA_ARGS__)
#define REG_PT(x, ...) PropertyTemplate* x = PropertyManager::addPropertyTemplate(__VA_ARGS__)
#define REG_PG(x, ...) PropertyGroupTemplate* x = PropertyManager::addPropertyGroupTemplate(__VA_ARGS__)
#define REG_AS(x, ...) AssetTemplate* x = AssetManager::addAssetTemplate(__VA_ARGS__)

inline static void dummy_func() {}

inline static void initProjectIoFunc() {
	using namespace Jupiter::Io;

	// FileTypes
	REG_FT(ftPng, FILE_TYPE_PNG, { "png" });
	REG_FT(ftCollada, FILE_TYPE_COLLADA, { "collada", "dae" });

	// PropertyValueTemplates
	REG_PV(pvTexNear, PV_TEXTURE_NEAREST, "nearest");
	REG_PV(pvTexLin, PV_TEXTURE_LINEAR, "linear");
	REG_PV(pvTexNearMipNear, PV_TEXTURE_NEAREST_MIPMAP_NEAREST, "nearest_mipmap_nearest");
	REG_PV(pvTexLinMipNear, PV_TEXTURE_LINEAR_MIPMAP_NEAREST, "linear_mipmap_nearest");
	REG_PV(pvTexNearMipLin, PV_TEXTURE_NEAREST_MIPMAP_LINEAR, "nearest_mipmap_linear");
	REG_PV(pvTexLinMipLin, PV_TEXTURE_LINEAR_MIPMAP_LINEAR, "linear_mipmap_linear");

	REG_PV(pvTexRep, PV_TEXTURE_REPEAT, "repeat");
	REG_PV(pvTexClampEdge, PV_TEXTURE_CLAMP_TO_EDGE, "clamp_to_edge");
	REG_PV(pvTexClampBorder, PV_TEXTURE_CLAMP_TO_BORDER, "clamp_to_border");
	REG_PV(pvTexMirRep, PV_TEXTURE_MIRRORED_REPEAT, "mirrored_repeat");
	REG_PV(pvTexMirClampEdge, PV_TEXTURE_MIRRORED_CLAMP_TO_EDGE, "mirrored_clamp_to_edge");

	// PropertyTemplates
	REG_PT(ptTextMinFilt, PI_TEXTURE_MIN_FILTER, "min_filter", { pvTexNear, pvTexLin, pvTexNearMipNear, pvTexLinMipNear, pvTexNearMipLin, pvTexLinMipLin });
	REG_PT(ptTexMagFilt, PI_TEXTURE_MAG_FILTER, "mag_filter", { pvTexNear , pvTexLin });
	REG_PT(ptTexWrapS, PI_TEXTURE_WRAP_S, "wrap_s", { pvTexRep, pvTexClampEdge, pvTexClampBorder, pvTexMirRep, pvTexMirClampEdge });
	REG_PT(ptTexWrapT, PI_TEXTURE_WRAP_T, "wrap_t", { pvTexRep, pvTexClampEdge, pvTexClampBorder, pvTexMirRep, pvTexMirClampEdge });
	REG_PT(ptTexWrapR, PI_TEXTURE_WRAP_R, "wrap_r", { pvTexRep, pvTexClampEdge, pvTexClampBorder, pvTexMirRep, pvTexMirClampEdge });

	// PropertyGroups
	REG_PG(pgTexture, PG_GROUP_TEXTURE, "texture_properties", { ptTextMinFilt, ptTexMagFilt, ptTexWrapS, ptTexWrapT, ptTexWrapR });

	// Assets
	REG_AS(asTexRgba, ASSET_TYPE_TEX_RGBA, { "tex_rgba" }, {{ftPng, dummy_func}}, {pgTexture});
	REG_AS(asModelStatic, ASSET_TYPE_MODEL_STATIC, { "model_static" }, {{ftCollada, dummy_func}}, {});
}

int main(int argc, char* argv[])
{
	Jupiter::Core::initializeCoreLogger(JPT_LOGGER_FLAG_PREFIX | JPT_LOGGER_FLAG_COLOR | JPT_LOGGER_FLAG_TIMESTAMP | JPT_LOGGER_FLAG_DATE);

    Jupiter::CommandParser commandParser(argc, argv);
    std::string cfgLocation;
    bool hasConfig = commandParser.findArgument("config", cfgLocation);
    if (!hasConfig) cfgLocation = "Config.io";
	
    Jupiter::Io::ProjectIo projectIo(cfgLocation, initProjectIoFunc);
    projectIo.run();

	Jupiter::Core::deleteCoreLogger();
}
