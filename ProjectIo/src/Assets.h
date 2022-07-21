#pragma once

#include <string>

#include "Core.h"

#include "AssetDefinitions.h"

#include "FileTypes.h"
#include "Properties.h"

namespace Jupiter::Io {

	typedef void (*AssetTransformFunction)();

	struct FileTypeTransformerPackage {
		FileType* m_SrcFileType;
		AssetTransformFunction m_TransformFunc;

		FileTypeTransformerPackage(FileType* ft, AssetTransformFunction func) :
			m_SrcFileType(ft),
			m_TransformFunc(func)
		{}
	};

	class AssetTemplate {

	public:
		AssetTemplate(uint32_t asset_id, const std::initializer_list<std::string>& asset_aliases, 
			std::initializer_list<FileTypeTransformerPackage> src_file_types, std::initializer_list<PropertyGroupTemplate*> property_groups);
		~AssetTemplate();

		bool isCompatibleWithSrcFileType(FileType* src_file_type);
		bool hasProperties() const;
		const std::vector<PropertyGroupTemplate*>& getAssetPropertyGroups() const;
		PropertyBufferIndexMap* getPropertyBufferIndexMap();

	private:
		uint32_t m_AssetId;
		std::vector<std::string> m_Aliases;
		std::vector<PropertyGroupTemplate*> m_PropertyGroups;

		AssetTransformFunction m_TransformFunctions[ENUM_FILE_TYPE_COUNT] = {};

		PropertyBufferIndexMap* m_PropertyBufferIndexMap = nullptr;

		friend class AssetManager;
	};

	class AssetManager {
		JPT_IO_MANAGER_CLASS(AssetManager)

	public:
		static AssetTemplate* addAssetTemplate(uint32_t asset_id, const std::initializer_list<std::string>& asset_aliases, 
			std::initializer_list<FileTypeTransformerPackage> src_file_types, std::initializer_list<PropertyGroupTemplate*> property_groups);

		static AssetTemplate* getAssetTemplateFromAlias(const std::string& alias);
		static AssetTemplate* getAssetTemplateFromId(uint32_t asset_type_id);

	private:
		AssetTemplate* m_AssetTemplates[ENUM_ASSET_TYPE_COUNT] = {};
	};

}
