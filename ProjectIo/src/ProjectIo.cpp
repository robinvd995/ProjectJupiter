#include "ProjectIo.h"

#include <memory>
#include <filesystem>

#include "JupiterCore/Log.h"
#include "JupiterCore/Xml.h"

#include "FileTypes.hpp"
#include "DataTransformer.hpp"

namespace Jupiter::Io {

#define JPT_IO_INPUT_IDENTIFIER_PNG "png"
#define JPT_IO_INPUT_IDENTIFIER_COLLADA "collada"

#define JPT_IO_OUTPUT_IDENTIFIER_TEX_RGBA "tex_rgba"
#define JPT_IO_OUTPUT_IDENTIFIER_MODEL_STATIC "model_static"

	static std::string s_FileOutputIdentifiers[] = {
		JPT_IO_FILE_TYPE_UNDEFINED_IDENTIFIER,
		"tex_rgba",
		"model_static"
	};

	enum class EnumFileInputType {
		UNDEFINED = JPT_IO_FILE_TYPE_UNDEFINED_ID,
		PNG = 1,
		COLLADA = 2,
	};

	enum class EnumFileOutputType {
		UNDEFINED = JPT_IO_FILE_TYPE_UNDEFINED_ID,
		TEX_RGBA = 1,
		MODEL_STATIC = 2,
	};

	ProjectIO::ProjectIO(std::string& cfgFile) : 
		m_ConfigFilePath(cfgFile)
	{

	}

	ProjectIO::~ProjectIO() {

	}

	inline static void ioAssetError(std::string id, std::string errortype, std::string errormessage) {
		JPT_ERROR("The following error occurred " + errortype + " for asset with id '" + id + "'\n    " + errormessage);
	}

	void ProjectIO::init() {

		// Init input file types
		FileTypeManager::addInputFileType((uint32_t)EnumFileInputType::PNG, JPT_IO_INPUT_IDENTIFIER_PNG);
		FileTypeManager::addInputFileType((uint32_t)EnumFileInputType::COLLADA, JPT_IO_INPUT_IDENTIFIER_COLLADA);

		// Init output file types
		FileTypeManager::addOutputFileType((uint32_t)EnumFileOutputType::TEX_RGBA, JPT_IO_OUTPUT_IDENTIFIER_TEX_RGBA);
		FileTypeManager::addOutputFileType((uint32_t)EnumFileOutputType::MODEL_STATIC, JPT_IO_OUTPUT_IDENTIFIER_MODEL_STATIC);

		// Init data transformers
		DataTransformManager::addDataTransformer((uint32_t)EnumFileInputType::PNG, (uint32_t)EnumFileOutputType::TEX_RGBA, &transformPngToTexRGBA);
		DataTransformManager::addDataTransformer((uint32_t)EnumFileInputType::COLLADA, (uint32_t)EnumFileOutputType::MODEL_STATIC, &transformColladaToStaticModel);
	}

	bool ProjectIO::load(std::string& error) {
		JPT_INFO("Loading config file: " + m_ConfigFilePath);

		bool cfgExists = std::filesystem::exists(m_ConfigFilePath);
		if (!cfgExists) { error = "Can't find config file with name " + m_ConfigFilePath + "'!"; return false; }

		// Parse the document and get the root node
		Xml::XmlDocument doc = Xml::parseXmlFile(m_ConfigFilePath, "io_configuration");
		const Xml::XmlNode root = doc.getRootNode();

		// Parse settings node
		const Xml::XmlNode nodeSettings = root.getFirstChild("settings");

		// Parse assets node
		const Xml::XmlNode nodeAssets = root.getFirstChild("included_assets");
		m_Config.m_Assets.m_Amount = nodeAssets.getAttributeAsInt("count");

		// Reserver the size of the asset buffer
		m_Config.m_Assets.m_AssetBuffer.reserve(m_Config.m_Assets.m_Amount);
		std::vector<IoAsset>& assetBuffer = m_Config.m_Assets.m_AssetBuffer;

		nodeAssets.iterate("asset", [&assetBuffer](const Xml::XmlNode& node) -> bool {

			// parse asset id and source
			std::string id = node.getAttribute("id").c_str();
			std::string src = node.getAttribute("src").c_str();

			// parse asset file input type
			std::string inputtype = node.getAttribute("inputtype");
			FileType& fit = FileTypeParser::parseFileInputTypeFromString(inputtype);
			if (!fit.isValid()) {
				JPT_ERROR("An error occurred while loading an asset config with id '" + id +
					"'\n    Input type with name '" + inputtype + "' is not registered!"); return false;
			}

			// parse asset file output type
			std::string outputtype = node.getAttribute("outputtype");
			FileType& fot = FileTypeParser::parseFileOutputTypeFromString(outputtype);
			if (!fot.isValid()) {
				JPT_ERROR("An error occurred while loading an asset config with id '" + id +
					"'\n    Output type with name '" + outputtype + "' is not registered!"); return false;
			}

			// create the asset object
			IoAsset asset;
			asset.m_InputType = fit.m_Id;
			asset.m_OutputType = fot.m_Id;
			asset.m_IdSize = (uint32_t)id.length();
			asset.m_SourceSize = (uint32_t)src.length();

#ifndef JPT_IO_CHECK_SIZE_ARRAYS
			if (asset.m_IdSize > JPT_IO_ASSET_ID_MAX_LENGTH) { 
				JPT_ERROR("An error occurred while loading an asset config with id '" + id + 
					"'\n    Asset id size exceeds the maximum size!");
				return false;
			}
			if (asset.m_SourceSize > JPT_IO_ASSET_SOURCE_MAX_LENGTH) { 
				JPT_ERROR("An error occurred while loading an asset config with id '" + id +
					"'\n    Asset src size exceeds the maximum size!");
				return false;
			}
#endif // JPT_IO_CHECK_SIZE_ARRAYS

			// copy the id and src into their containers
			memcpy(&asset.m_Id, id.c_str(), asset.m_IdSize);
			memcpy(&asset.m_Source, src.c_str(), asset.m_SourceSize);

			// push the asset into the buffer
			JPT_INFO("Loaded asset: id='" + id + "', src='" + src + "', inputtype='" + fit.m_Identifier + "', outputtype='" + fot.m_Identifier + "'");
			assetBuffer.push_back(asset);

			return true;
		});

		return true;
	}

	bool ProjectIO::execute(std::string& error) {
		for (IoAsset& asset : m_Config.m_Assets.m_AssetBuffer) {
			std::string assetId = std::string(asset.m_Id, asset.m_Id + asset.m_IdSize);
			std::string assetSrc = std::string(asset.m_Source, asset.m_Source + asset.m_SourceSize);
			uint32_t inType = asset.m_InputType;
			uint32_t outType = asset.m_OutputType;

			DataTransformFunction transformFunction = DataTransformManager::getTransformFunction(inType, outType);

			if (transformFunction == nullptr) {
				std::string sInType = FileTypeManager::getInputStringFromId(inType);
				std::string sOutType = FileTypeManager::getOutputStringFromId(outType);
				ioAssetError(assetId, "UNKNOWN_TRANSFORMATION", "There is no transformer found for '" + sInType + "' to '" + sOutType + "'");
				continue;
			}

			transformFunction({});

			bool srcExists = std::filesystem::exists(std::string(asset.m_Source));
			if (!srcExists) { ioAssetError(assetId, "MISSING_FILE", "Cannot find source file '" + assetSrc + "'"); continue; }
		}
		return true;
	}

	bool ProjectIO::release(std::string& error) {

		// Free the asset buffer
		return true;
	}

}
