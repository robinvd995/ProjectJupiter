#include "ProjectIo.h"

#include <memory>
#include <filesystem>

#include "JupiterCore/Core.h"
#include "JupiterCore/Log.hpp"
#include "JupiterCore/Formatter.hpp"
#include "JupiterCore/Xml.h"

#include "Core.h"
#include "DataTransformer.hpp"
#include "Properties.h"
#include "FileTypes.h"

namespace Jupiter::Io {

	ProjectIo::ProjectIo(std::string& cfgFile, init_func func) :
		m_ConfigFilePath(cfgFile),
		m_InitFunction(func)
	{
		
	}

	ProjectIo::~ProjectIo() {

	}

	//inline static void ioAssetError(std::string id, std::string errortype, std::string errormessage) {
		//JPT_IO_ERROR("The following error occurred " + errortype + " for asset with id '" + id + "'\n    " + errormessage);
	//	JPT_IO_ERROR("The following error occured [0] for asset with id '[1]'\n    [2]", id, errortype, errormessage);
	//}

	void ProjectIo::run() {
		// Initialize logger
		Jupiter::Io::initializeIoLogger(JPT_LOGGER_FLAG_PREFIX | JPT_LOGGER_FLAG_COLOR | JPT_LOGGER_FLAG_TIMESTAMP | 
			JPT_LOGGER_FLAG_NAME);

		// Initialize Managers
		//AssetPropertyManager::s_Instance = new AssetPropertyManager();
		FileTypeManager::s_Instance = new FileTypeManager();
		DataTransformManager::s_Instance = new DataTransformManager();
		PropertyManager::s_Instance = new PropertyManager();

		// Run the init function given to this object during its creation
		m_InitFunction();

		std::string error;
		if (!load(error)) { std::cout << error << std::endl; return; }
		if (!execute(error)) { std::cout << error << std::endl; return; }
		if (!release(error)) { std::cout << error << std::endl; return; }

		// Delete Managers
		//delete AssetPropertyManager::s_Instance;
		delete FileTypeManager::s_Instance;
		delete DataTransformManager::s_Instance;
		delete PropertyManager::s_Instance;

		// Delete Logger
		Jupiter::Io::deleteIoLogger();
	}

	bool ProjectIo::load(std::string& error) {
		JPT_IO_INFO("Loading config file: [0]", m_ConfigFilePath);

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
			FileType* fit = FileTypeManager::getFileTypeFromAlias(inputtype);
			if (!fit) {
				JPT_IO_ERROR("An error occurred while loading an asset config with id '[0]'\n    \
					Input type with name '[1]' is not registered!", id, inputtype); 
				return false;
			}

			// parse asset file output type
			std::string outputtype = node.getAttribute("outputtype");
			FileType* fot = FileTypeManager::getFileTypeFromAlias(outputtype);
			if (!fot) {
				JPT_IO_ERROR("An error occurred while loading an asset config with id '[0]'\n    \
					Output type with name '[1]' is not registered!", id, outputtype); 
				return false;
			}

			// create the asset object
			IoAsset asset;
			asset.m_InputType = fit;
			asset.m_OutputType = fot;
			asset.m_IdSize = (uint32_t)id.length();
			asset.m_SourceSize = (uint32_t)src.length();

#ifndef JPT_IO_CHECK_SIZE_ARRAYS
			if (asset.m_IdSize > JPT_IO_ASSET_ID_MAX_LENGTH) { 
				JPT_IO_ERROR("An error occurred while loading an asset config with id '[0]'\n    Asset id size exceeds the maximum size!", id);
				return false;
			}
			if (asset.m_SourceSize > JPT_IO_ASSET_SOURCE_MAX_LENGTH) { 
				JPT_IO_ERROR("An error occurred while loading an asset config with id '[0]'\n    Asset src size exceeds the maximum size!", id);
				return false;
			}
#endif // JPT_IO_CHECK_SIZE_ARRAYS

			// copy the id and src into their containers
			memcpy(&asset.m_Id, id.c_str(), asset.m_IdSize);
			memcpy(&asset.m_Source, src.c_str(), asset.m_SourceSize);

			// push the asset into the buffer
			JPT_IO_INFO("Loaded asset: id='[0]', src='[1]', inputtype='[2]', outputtype='[3]'", id, src, fit->m_FileTypeId, fot->m_FileTypeId);
			assetBuffer.push_back(asset);

			//Properties
			bool hasTextureProperties = node.hasChildNode("texture_properties");
			//if (!hasTextureProperties) ioAssetError(id, "TEST", "no texture properties node");
			//const Xml::XmlNode texPropsNode = node.getFirstChild("texture_properties");


			return true;
		});

		return true;
	}

	bool ProjectIo::execute(std::string& error) {
		for (IoAsset& asset : m_Config.m_Assets.m_AssetBuffer) {
			std::string assetId = std::string(asset.m_Id, asset.m_Id + asset.m_IdSize);
			std::string assetSrc = std::string(asset.m_Source, asset.m_Source + asset.m_SourceSize);
			FileType* inType = asset.m_InputType;
			FileType* outType = asset.m_OutputType;

			//DataTransformFunction transformFunction = DataTransformManager::getTransformFunction(inType, outType);

			//if (transformFunction == nullptr) {
				//std::string sInType = FileTypeManager::getInputStringFromId(inType);
				//std::string sOutType = FileTypeManager::getOutputStringFromId(outType);
				//ioAssetError(assetId, "UNKNOWN_TRANSFORMATION", "There is no transformer found for '" + sInType + "' to '" + sOutType + "'");
				//continue;
			//}

			//transformFunction({});

			bool srcExists = std::filesystem::exists(std::string(asset.m_Source));
			//if (!srcExists) { ioAssetError(assetId, "MISSING_FILE", "Cannot find source file '" + assetSrc + "'"); continue; }
		}
		return true;
	}

	bool ProjectIo::release(std::string& error) {

		// Free the asset buffer
		return true;
	}

}
