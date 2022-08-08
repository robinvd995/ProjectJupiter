#pragma once

#include <string>

#include "Core.h"

#include "AssetDefinitions.h"

#include "FileTypes.h"
#include "Properties.h"

namespace Jupiter::Io {

	typedef void (*AssetTransformFunction)();

	/// <summary>
	/// 
	/// </summary>
	struct FileTypeTransformerPackage {
		FileType* m_SrcFileType;
		AssetTransformFunction m_TransformFunc;

		FileTypeTransformerPackage(FileType* ft, AssetTransformFunction func) :
			m_SrcFileType(ft),
			m_TransformFunc(func)
		{}
	};

	/// <summary>
	/// 
	/// </summary>
	class AssetTemplate {

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="asset_id"></param>
		/// <param name="asset_aliases"></param>
		/// <param name="src_file_types"></param>
		/// <param name="property_groups"></param>
		AssetTemplate(uint32_t asset_id, const std::initializer_list<std::string>& asset_aliases, 
			std::initializer_list<FileTypeTransformerPackage> src_file_types, std::initializer_list<PropertyGroupTemplate*> property_groups);
		~AssetTemplate();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src_file_type"></param>
		/// <returns></returns>
		bool isCompatibleWithSrcFileType(FileType* src_file_type);

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool hasProperties() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::vector<PropertyGroupTemplate*>& getAssetPropertyGroups() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		PropertyBufferIndexMap* getPropertyBufferIndexMap();

	private:
		uint32_t m_AssetId;
		std::vector<std::string> m_Aliases;
		std::vector<PropertyGroupTemplate*> m_PropertyGroups;

		AssetTransformFunction m_TransformFunctions[ENUM_FILE_TYPE_COUNT] = {};

		PropertyBufferIndexMap* m_PropertyBufferIndexMap = nullptr;

		friend class AssetManager;
	};

	/// <summary>
	/// 
	/// </summary>
	class AssetManager {
		JPT_IO_MANAGER_CLASS(AssetManager)

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="asset_id"></param>
		/// <param name="asset_aliases"></param>
		/// <param name="src_file_types"></param>
		/// <param name="property_groups"></param>
		/// <returns></returns>
		static AssetTemplate* addAssetTemplate(uint32_t asset_id, const std::initializer_list<std::string>& asset_aliases, 
			std::initializer_list<FileTypeTransformerPackage> src_file_types, std::initializer_list<PropertyGroupTemplate*> property_groups);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="alias"></param>
		/// <returns></returns>
		static AssetTemplate* getAssetTemplateFromAlias(const std::string& alias);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="asset_type_id"></param>
		/// <returns></returns>
		static AssetTemplate* getAssetTemplateFromId(uint32_t asset_type_id);

	private:
		AssetTemplate* m_AssetTemplates[ENUM_ASSET_TYPE_COUNT] = {};
	};

}
