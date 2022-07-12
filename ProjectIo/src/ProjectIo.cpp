#include "ProjectIo.h"

#include <memory>
#include <filesystem>

#include "JupiterCore/Core.h"
#include "JupiterCore/Log.hpp"
#include "JupiterCore/Xml.h"

#include "FileTypes.hpp"
#include "DataTransformer.hpp"
#include "AssetProperties.h"

namespace Jupiter::Io {

	ProjectIo::ProjectIo(std::string& cfgFile, init_func func) :
		m_ConfigFilePath(cfgFile),
		m_InitFunction(func)
	{
		
	}

	ProjectIo::~ProjectIo() {

	}

	inline static void ioAssetError(std::string id, std::string errortype, std::string errormessage) {
		JPT_ERROR("The following error occurred " + errortype + " for asset with id '" + id + "'\n    " + errormessage);
	}

	void ProjectIo::run() {
		
		// Initialize Managers
		AssetPropertyManager::s_Instance = new AssetPropertyManager();
		FileTypeManager::s_Instance = new FileTypeManager();
		DataTransformManager::s_Instance = new DataTransformManager();

		// Run the init function given to this object during its creation
		m_InitFunction();

		std::string error;
		if (!load(error)) { std::cout << error << std::endl; return; }
		if (!execute(error)) { std::cout << error << std::endl; return; }
		if (!release(error)) { std::cout << error << std::endl; return; }

		// Delete Managers
		delete AssetPropertyManager::s_Instance;
		delete FileTypeManager::s_Instance;
		delete DataTransformManager::s_Instance;
	}

	bool ProjectIo::load(std::string& error) {
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

			//Properties
			bool hasTextureProperties = node.hasChildNode("texture_properties");
			if (!hasTextureProperties) ioAssetError(id, "TEST", "no texture properties node");
			//const Xml::XmlNode texPropsNode = node.getFirstChild("texture_properties");


			return true;
		});

		return true;
	}

	bool ProjectIo::execute(std::string& error) {
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

	bool ProjectIo::release(std::string& error) {

		// Free the asset buffer
		return true;
	}

}
