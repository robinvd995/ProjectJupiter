#include "Properties.h"

#include "FileTypes.h"

#include <set>

namespace Jupiter::Io {

	// ----- START PropertyValueTemplate -----

	PropertyValueTemplate::PropertyValueTemplate(uint32_t id, const std::string& name) :
		m_PropertyValueId(id),
		m_PropertyValueName(name)
	{}

	PropertyValueTemplate::~PropertyValueTemplate() {}

	// -----  END  PropertyValueTemplate -----
	
	// ----- START PropertyTemplate -----

	PropertyTemplate::PropertyTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyValueTemplate>& accepted_values) :
		m_PropertyId(id),
		m_PropertyName(name),
		m_AcceptedValues(accepted_values),
		m_PropertyBufferSize(4)
	{}

	PropertyTemplate::~PropertyTemplate() {}

	// -----  END  PropertyTemplate -----

	// ----- START PropertyGroupTemplate -----

	PropertyGroupTemplate::PropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate>& properties) :
		m_PropertyGroupTemplateId(id),
		m_PropertyGroupTemplateName(name),
		m_Properties(properties),
		m_PropertyGroupBufferSize(0)
	{}

	PropertyGroupTemplate::~PropertyGroupTemplate() {}

	// ----  END  PropertyGroupTemplate -----

	// ----- START PropertyContainerTemplate -----

	//PropertyContainerTemplate::PropertyContainerTemplate(uint32_t file_type_id, uint32_t usage, BufferPropertyTemplate<PropertyGroupTemplate>& groups) :
	//	m_PropertyContainerTemplateId(file_type_id),
	//	m_FileUsage(usage),
	//	m_Groups(groups)
	//{}
	//
	//PropertyContainerTemplate::~PropertyContainerTemplate() {}

	// ----  END  PropertyContainerTemplate -----

	// ----- START PropertyBufferIndexMap -----

	PropertyBufferIndexMap::PropertyBufferIndexMap() :
		m_BufferSize(0)
	{
		//m_PropertySizes = (uint8_t*)malloc(sizeof(uint8_t) * m_PropertyCount);
	}

	PropertyBufferIndexMap::~PropertyBufferIndexMap() {
		//free(m_PropertySizes);
	}

	// ----  END  PropertyBufferIndexMap -----

	// ----- START PropertyBuffer -----

	PropertyBuffer::PropertyBuffer(PropertyBufferIndexMap* index_map) :
		m_IndexMap(index_map)
	{
		m_Buffer.allocate<char>(index_map->m_BufferSize);
	}

	PropertyBuffer::~PropertyBuffer() {
		m_Buffer.freeBuffer();
	}

	void PropertyBuffer::setPropertyDefaultValue(uint32_t group_id, uint32_t property_id) {
		if (!moveIterator(group_id, property_id)) return;
		uint32_t valueTemplate = PropertyManager::getDefaultValueForProperty(property_id);
		m_Buffer.write<uint32_t>(valueTemplate);
	}

	void PropertyBuffer::setPropertyValue(uint32_t group_id, uint32_t property_id, uint32_t value) {
		if (!moveIterator(group_id, property_id)) return;
		m_Buffer.write<uint32_t>(value);
	}

	uint32_t PropertyBuffer::getPropertyValue(uint32_t group_id, uint32_t property_id) {
		if (!moveIterator(group_id, property_id)) return 0;
		return m_Buffer.read<uint32_t>();
	}

	bool PropertyBuffer::moveIterator(uint32_t group_id, uint32_t property_id) {
		for (PropertyIndexMapEntry& entry : m_IndexMap->m_IndexMap) {
			GroupIndex& gi = entry.first;
			if (std::get<0>(gi) != group_id) continue;
			for (PropertyIndex& pi : entry.second) if (std::get<0>(pi) == property_id) {
				uint32_t location = std::get<1>(gi) + std::get<1>(pi);
				m_Buffer.moveIterator(location);
				return true;
			}
		}
		return false;
	}

	// ----  END  PropertyBuffer -----

	// ----- START PropertyManager -----

	PropertyManager::PropertyManager() {}

	PropertyManager::~PropertyManager() {}

	PropertyValueTemplate* PropertyManager::addPropertyValueTemplate(uint32_t id, const std::string& name) {
		if (s_Instance->m_ValueTemplates[id]) return s_Instance->m_ValueTemplates[id];
		PropertyValueTemplate* valueTemplate = new PropertyValueTemplate(id, name);
		s_Instance->m_ValueTemplates[id] = valueTemplate;
		return valueTemplate;
	}

	PropertyTemplate* PropertyManager::addPropertyTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyValueTemplate> accepted_values) {
		if (s_Instance->m_PropertyTemplates[id]) return s_Instance->m_PropertyTemplates[id];
		PropertyTemplate* propertyTemplate = new PropertyTemplate(id, name, accepted_values);
		s_Instance->m_PropertyTemplates[id] = propertyTemplate;
		return propertyTemplate;
	}

	PropertyGroupTemplate* PropertyManager::addPropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate> values) {
		if (s_Instance->m_GroupTemplates[id]) return s_Instance->m_GroupTemplates[id];
		PropertyGroupTemplate* groupTemplate = new PropertyGroupTemplate(id, name, values);

		uint32_t curIndex = 0;
		for (PropertyTemplate* val : values.m_Buffer) {
			uint32_t bufSize = val->m_PropertyBufferSize;
			groupTemplate->m_PropertyGroupBufferSize += bufSize;
			groupTemplate->m_PropertyIndicies.push_back({ val->m_PropertyId, curIndex, bufSize });
			curIndex += bufSize;
		}

		s_Instance->m_GroupTemplates[id] = groupTemplate;
		return groupTemplate;
	}

	//PropertyContainerTemplate* PropertyManager::addPropertyContainerTemplate(uint32_t file_type_id, uint32_t usage, BufferPropertyTemplate<PropertyGroupTemplate> groups) {
	//	if (s_Instance->m_ContainerTemplates[file_type_id]) return s_Instance->m_ContainerTemplates[file_type_id];
	//	PropertyContainerTemplate* containerTemplate = new PropertyContainerTemplate(file_type_id, usage, groups);
	//	s_Instance->m_ContainerTemplates[file_type_id] = containerTemplate;
	//	return containerTemplate;
	//}

	PropertyBufferIndexMap* PropertyManager::createPropertyBufferIndexMap(std::initializer_list<uint32_t> group_ids) {
		std::set<uint32_t> groupids(group_ids.begin(), group_ids.end());
		PropertyBufferIndexMap* indexMap = new PropertyBufferIndexMap();

		for (uint32_t id : groupids) {
			PropertyGroupTemplate* groupTemplate = s_Instance->m_GroupTemplates[id];
			if (!groupTemplate) continue;
			GroupIndex groupIndex = { id, indexMap->m_BufferSize, groupTemplate->m_PropertyGroupBufferSize };
			
			std::vector<PropertyIndex> propertyIndices;
			uint32_t curPropertyIndex = 0;
			for (PropertyTemplate* prop : groupTemplate->m_Properties.m_Buffer) {
				propertyIndices.push_back({ prop->m_PropertyId, curPropertyIndex, prop->m_PropertyBufferSize });
				curPropertyIndex += prop->m_PropertyBufferSize;
			}

			indexMap->m_BufferSize += groupTemplate->m_PropertyGroupBufferSize;
			indexMap->m_IndexMap.push_back({ groupIndex, propertyIndices });
		}
		return indexMap;
	}

	PropertyBuffer* PropertyManager::createPropertyBuffer(PropertyBufferIndexMap* index_map) {
		// PropertyBuffer* propertyBuffer = new PropertyBuffer();
		// propertyBuffer->m_Buffer = (char*)malloc(index_map->m_BufferSize);
		// propertyBuffer->m_IndexMap = index_map;
		// return propertyBuffer;
		return new PropertyBuffer(index_map);
	}

	uint32_t PropertyManager::getDefaultValueForProperty(uint32_t property_id) {
		PropertyTemplate* propTemplate = s_Instance->m_PropertyTemplates[property_id];
		return propTemplate->m_AcceptedValues.m_Buffer[0]->m_PropertyValueId;
	}

	// -----  END  PropertyManager -----
}
