#include "AssetProperties.h"

#include <iostream>
#include <memory>

namespace Jupiter::Io {

	// ----- START AssetPropertyGroup -----

	AssetPropertyGroup::AssetPropertyGroup(uint32_t group_id, const std::string& group_str_identifier, uint32_t property_amount) :
		m_GroupId(group_id),
		m_GroupStrIdentifier(group_str_identifier),
		m_Amount(property_amount)
	{
		m_Buffer = (uint32_t*)malloc(sizeof(uint32_t) * property_amount);
		m_IdentifierLengthBuffer = (uint32_t*)malloc(sizeof(uint32_t) * property_amount);
		m_IdentifierStrBuffer = (char*)malloc((size_t)property_amount * JPT_IO_PROPERTIES_IDENTIFIER_MAX_LENGTH);
	}

	AssetPropertyGroup::~AssetPropertyGroup() {
		free(m_Buffer);
		free(m_IdentifierLengthBuffer);
		free(m_IdentifierStrBuffer);
	}

	void AssetPropertyGroup::addProperty(uint32_t index, uint32_t property_id, const std::string& str_identifier) {
		size_t strSize = str_identifier.size();
		if (strSize > JPT_IO_PROPERTIES_IDENTIFIER_MAX_LENGTH) {
			strSize = JPT_IO_PROPERTIES_IDENTIFIER_MAX_LENGTH;
			std::cout << "error, string size to big!" << std::endl; // TODO create an actually usefull error message
		}
		m_Buffer[index] = property_id;
		m_IdentifierLengthBuffer[index] = (uint32_t)strSize;
		memcpy(&m_IdentifierStrBuffer[index * JPT_IO_PROPERTIES_IDENTIFIER_MAX_LENGTH], str_identifier.c_str(), strSize);
	}

	const uint32_t AssetPropertyGroup::getGroupId() {
		return m_GroupId;
	}

	const std::string& AssetPropertyGroup::getGroupStrIdentifier() {
		return m_GroupStrIdentifier;
	}

	const std::string AssetPropertyGroup::getPropertyStringIdentifier(uint32_t index) {
		uint32_t strSize = m_IdentifierLengthBuffer[index];
		return std::string(&m_IdentifierStrBuffer[index * JPT_IO_PROPERTIES_IDENTIFIER_MAX_LENGTH], strSize);
	}

	const uint32_t AssetPropertyGroup::getPropertyId(uint32_t index) {
		return m_Buffer[index];
	}

#ifndef JPT_IO_IGNORE_VALID_PROPERTY_VALUES

	void AssetPropertyGroup::addValidPropertyValue(uint32_t prop, uint32_t prop_value) {

		bool foundProperty = false;

		for (std::pair<uint32_t, std::vector<uint32_t>>& it : m_PropertiesValidValues) {
			if (it.first == prop) {
				it.second.push_back(prop_value);
				foundProperty = true;
				break;
			}
		}

		if (!foundProperty) std::cout << "Error inserting value into valid property map!\n";
	}

#endif // JPT_IO_IGNORE_VALID_PROPERTY_VALUES

	// ----- END AssetPropertyGroup -----

	// ----- START AssetPropertyManager -----

	AssetPropertyManager::AssetPropertyManager()
	{

	}

	AssetPropertyManager::~AssetPropertyManager() {
		for (AssetPropertyGroup* group : m_PropertyGroups) delete group;
	}

	AssetPropertyGroup* AssetPropertyManager::registerPropertyGroup(uint32_t group_id, const std::string& group_str_identifier, uint32_t property_amount) {
		AssetPropertyGroup* group = new AssetPropertyGroup(group_id, group_str_identifier, property_amount);
		s_Instance->m_PropertyGroups[group_id] = group;
		return group;
	}

	const AssetPropertyGroup* AssetPropertyManager::getPropertyGroup(uint32_t group_id) {
		return s_Instance->m_PropertyGroups[group_id];
	}

	const AssetPropertyGroup* AssetPropertyManager::getPropertyGroup(const std::string& group_str_identifier) {
		for (AssetPropertyGroup* group : s_Instance->m_PropertyGroups) {
			if (group && group->getGroupStrIdentifier() == group_str_identifier) return group;
		}
		return nullptr;
	}


	// ----- END AssetPropertyManager -----
}