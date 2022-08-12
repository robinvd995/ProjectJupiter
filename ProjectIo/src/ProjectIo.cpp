#include "ProjectIo.h"

#include <memory>
#include <filesystem>

#include "JupiterCore/Core.h"
#include "JupiterCore/Log.hpp"
#include "JupiterCore/Formatter.hpp"
#include "JupiterCore/Xml.h"

#include "Core.h"

#include "Properties.h"
#include "FileTypes.h"
#include "Assets.h"

#include "JptMemory.h"

namespace Jupiter::Io {

	ProjectIo::ProjectIo(std::string& cfgFile, init_func func) :
		m_ConfigFilePath(cfgFile),
		m_InitFunction(func)
	{
		
	}

	ProjectIo::~ProjectIo() {

	}

	void ProjectIo::run() {
		// Initialize logger
		Jupiter::Io::initializeIoLogger(JPT_LOGGER_FLAG_PREFIX | JPT_LOGGER_FLAG_COLOR | JPT_LOGGER_FLAG_TIMESTAMP | 
			JPT_LOGGER_FLAG_NAME);

		MemoryManager::s_Instance = new MemoryManager();

		bool cfgExists = std::filesystem::exists(m_ConfigFilePath);
		if (!cfgExists) return;
		Xml::XmlDocument doc = Xml::parseXmlFile(m_ConfigFilePath, JPT_IO_CONFIG_ROOT_NODE);

		// Initialize Managers
		FileTypeManager::s_Instance = new FileTypeManager();
		PropertyManager::s_Instance = new PropertyManager();
		AssetManager::s_Instance = new AssetManager();

		// Run the init function given to this object during its creation
		m_InitFunction();

		std::string error;
		if (!load(error, doc)) { std::cout << error << std::endl; return; }
		if (!execute(error, doc)) { std::cout << error << std::endl; return; }
		if (!release(error)) { std::cout << error << std::endl; return; }

		// Delete Managers
		delete FileTypeManager::s_Instance;
		delete PropertyManager::s_Instance;
		delete AssetManager::s_Instance;

		delete MemoryManager::s_Instance;

		// Delete Logger
		Jupiter::Io::deleteIoLogger();
	}

	bool ProjectIo::load(std::string& error, Xml::XmlDocument& doc) {
		JPT_IO_INFO("Loading config file: [0]", m_ConfigFilePath);

		const Xml::XmlNode root = doc.getRootNode();

		// Parse settings node
		const Xml::XmlNode nodeSettings = root.getFirstChild(JPT_IO_CONFIG_SETTINGS_NODE);
		const Xml::XmlNode nodeOutput = nodeSettings.getFirstChild(JPT_IO_CONFIG_OUTPUT_NODE);
		m_Config.m_OututStructure = (IoOutputStructure)nodeOutput.getAttributeAsInt(JPT_IO_CONFIG_OUTPUT_STRUCTURE_ATTRIB);

		// Parse assets node
		const Xml::XmlNode nodeAssets = root.getFirstChild(JPT_IO_CONFIG_INCLUDED_ASSETS);
		m_Config.m_IncludedAssetCount = nodeAssets.getAttributeAsInt(JPT_IO_CONFIG_GENERAL_ATTRIB_COUNT);

		return true;
	}

	bool ProjectIo::execute(std::string& error, Xml::XmlDocument& doc) {
		const Xml::XmlNode root = doc.getRootNode();
		const Xml::XmlNode nodeAssets = root.getFirstChild("included_assets");

		nodeAssets.iterate("asset", [](const Xml::XmlNode& node) -> bool {
			// parse asset id and source
			std::string id = node.getAttribute(JPT_IO_CONFIG_ASSET_ATTRIB_ID).c_str();
			std::string src = node.getAttribute(JPT_IO_CONFIG_ASSET_ATTRIB_SRC).c_str();

			// parse asset file src type
			std::string strSrcType = node.getAttribute(JPT_IO_CONFIG_ASSET_ATTRIB_SRC_TYPE);
			FileType* srcType = FileTypeManager::getFileTypeFromAlias(strSrcType);
			if (!srcType) {
				JPT_IO_ERROR("An error occurred while loading an asset config with id '[0]'\n    Source type with name '[1]' is not registered!", id, strSrcType);
				return false;
			}

			// parse asset file output type
			std::string strAssetType = node.getAttribute(JPT_IO_CONFIG_ASSET_ATTRIB_TYPE);
			AssetTemplate* assetTemplate = AssetManager::getAssetTemplateFromAlias(strAssetType);
			if (!assetTemplate) {
				JPT_IO_ERROR("An error occurred while loading an asset config with id '[0]'\n    Asset type with name '[1]' is not registered!", id, strAssetType);
				return false;
			}

			JPT_IO_INFO("Asset found: id=[0], src=[1], src_type=[2], asset_type=[3]", id, src, strSrcType, strAssetType);

			// Check if the given template is compatible with the given src file, if not throw an error
			if (!assetTemplate->isCompatibleWithSrcFileType(srcType)) {
				JPT_IO_ERROR("An error occurred while loading an asset with id '[0]'\n    Asset type '[1]' is not compatible with src file of type '[2]'",
					id, strAssetType, strSrcType);
				return false;
			}

			PropertyBuffer* propBuffer = nullptr;
			if (assetTemplate->hasProperties()) {
				propBuffer = PropertyManager::createPropertyBuffer(assetTemplate->getPropertyBufferIndexMap());
				for (PropertyGroupTemplate* pgt : assetTemplate->getAssetPropertyGroups()) {
					Xml::XmlNode propNode = node.getFirstChild(pgt->getPropertyGroupTemplateName().c_str());
					for (PropertyTemplate* pt : pgt->getPropertyTemplates()) {
						const std::string propAttribValue = propNode.getAttribute(pt->getPropertyName().c_str());
						uint32_t propertyValue = PropertyManager::getValueForPropertyAndValue(pt, propAttribValue);
						propBuffer->setPropertyValue(pgt->getPropertyGroupTemplateId(), pt->getPropertyTemplateId(), propertyValue);
					}
				}
			}

//			if (propBuffer) {
//				JPT_IO_INFO("min_filter=[0]", propBuffer->getPropertyValue(PG_GROUP_TEXTURE, PI_TEXTURE_MIN_FILTER));
//				JPT_IO_INFO("mag_filter=[0]", propBuffer->getPropertyValue(PG_GROUP_TEXTURE, PI_TEXTURE_MAG_FILTER));
//				JPT_IO_INFO("wrap_s=[0]", propBuffer->getPropertyValue(PG_GROUP_TEXTURE, PI_TEXTURE_WRAP_S));
//				JPT_IO_INFO("wrap_t=[0]", propBuffer->getPropertyValue(PG_GROUP_TEXTURE, PI_TEXTURE_WRAP_T));
//				JPT_IO_INFO("wrap_r=[0]", propBuffer->getPropertyValue(PG_GROUP_TEXTURE, PI_TEXTURE_WRAP_R));
//			}

		});
		return true;
	}

	bool ProjectIo::release(std::string& error) {

		// Free the asset buffer
		return true;
	}

}
