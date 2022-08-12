#include "Assets.h"

#include "JptMemory.h"

namespace Jupiter::Io {

	// ----- START AssetTemplate -----

	AssetTemplate::AssetTemplate(uint32_t asset_id, const std::initializer_list<std::string>& asset_aliases,
		std::initializer_list<FileTypeTransformerPackage> src_file_types, std::initializer_list<PropertyGroupTemplate*> property_groups) :

		m_AssetId(asset_id),
		m_Aliases(asset_aliases),
		m_PropertyGroups(property_groups)
	{
		for (FileTypeTransformerPackage fttp : src_file_types) {
			m_TransformFunctions[fttp.m_SrcFileType->getFileTypeId()] = fttp.m_TransformFunc;
		}
		m_PropertyBufferIndexMap = PropertyManager::createPropertyBufferIndexMap(m_PropertyGroups);
	}

	AssetTemplate::~AssetTemplate() {

	}

	bool AssetTemplate::isCompatibleWithSrcFileType(FileType* src_file_type) {
		return m_TransformFunctions[src_file_type->getFileTypeId()] != nullptr;
	}

	bool AssetTemplate::hasProperties() const {
		return m_PropertyGroups.size() > 0;
	}

	const std::vector<PropertyGroupTemplate*>& AssetTemplate::getAssetPropertyGroups() const {
		return m_PropertyGroups;
	}

	PropertyBufferIndexMap* AssetTemplate::getPropertyBufferIndexMap() {
		return m_PropertyBufferIndexMap;
	}

	// -----  END  AssetTemplate -----


	// ----- START AssetManager -----

	AssetManager::AssetManager() {

	}

	AssetManager::~AssetManager() {

	}

	AssetTemplate* AssetManager::addAssetTemplate(uint32_t asset_id, const std::initializer_list<std::string>& asset_aliases, 
		std::initializer_list<PropertyGroupTemplate*> property_groups, std::initializer_list<FileTypeTransformerPackage> src_file_types) {

		AssetTemplate* assetTemplate = createPtr<AssetTemplate>(asset_id, asset_aliases, src_file_types, property_groups);
		s_Instance->m_AssetTemplates[asset_id] = assetTemplate;
		return assetTemplate;
	}

	AssetTemplate* AssetManager::getAssetTemplateFromAlias(const std::string& alias) {
		for (int i = 0; i < ENUM_ASSET_TYPE_COUNT; i++) {
			AssetTemplate* at = s_Instance->m_AssetTemplates[i];
			if (!at) continue;
			for (const std::string& atAlias : at->m_Aliases)
				if (alias == atAlias) return at;
		}
		return nullptr;
	}

	AssetTemplate* AssetManager::getAssetTemplateFromId(uint32_t asset_type_id) {
		return s_Instance->m_AssetTemplates[asset_type_id];
	}

	// -----  END  AssetManager -----
}
