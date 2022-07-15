#pragma once

#include <cstdint>
#include <vector>
#include <string>

//#define JPT_IO_PROPERTIES_CONTAINER_MAX 16

//#define JPT_IO_IGNORE_VALID_PROPERTY_VALUES

#define JPT_IO_PROPERTIES_IDENTIFIER_MAX_LENGTH 32
#define JPT_IO_PROPERTIES_GROUP_MAX_COUNT 4

namespace Jupiter::Io {

	class AssetPropertyGroup {

	public:
		AssetPropertyGroup() = delete;
		AssetPropertyGroup(AssetPropertyGroup&) = delete;
		AssetPropertyGroup(uint32_t group_id, const std::string& group_str_identifier, uint32_t property_amount);
		~AssetPropertyGroup();

		void addProperty(uint32_t index, uint32_t property_id, const std::string& str_identifier);

		const uint32_t getGroupId();
		const std::string& getGroupStrIdentifier();
		const std::string getPropertyStringIdentifier(uint32_t index);
		const uint32_t getPropertyId(uint32_t index);

	private:
		uint32_t m_GroupId;
		const std::string m_GroupStrIdentifier;
		uint32_t m_Amount;
		uint32_t* m_Buffer;
		uint32_t* m_IdentifierLengthBuffer;
		char* m_IdentifierStrBuffer;

#ifndef JPT_IO_IGNORE_VALID_PROPERTY_VALUES
	public:
		void addValidPropertyValue(uint32_t prop, uint32_t prop_value);

	private:
		std::vector<std::pair<uint32_t,std::vector<uint32_t>>> m_PropertiesValidValues;
#endif // JPT_IO_IGNORE_VALID_PROPERTY_VALUES
	};

	class ProjectIo;

	class AssetPropertyManager {

	public:
		AssetPropertyManager(AssetPropertyManager&) = delete;

		static AssetPropertyGroup* registerPropertyGroup(uint32_t group_id, const std::string& group_str_identifier, uint32_t property_amount);
		static const AssetPropertyGroup* getPropertyGroup(uint32_t group_id);
		static const AssetPropertyGroup* getPropertyGroup(const std::string& group_str_identifier);

	private:
		AssetPropertyManager();
		~AssetPropertyManager();

	private:
		inline static AssetPropertyManager* s_Instance = nullptr;

		AssetPropertyGroup* m_PropertyGroups[JPT_IO_PROPERTIES_GROUP_MAX_COUNT] = { };

		friend class ProjectIo;
	};
}
