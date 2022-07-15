#include "Properties.h"

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
		m_AcceptedValues(accepted_values)
	{}

	PropertyTemplate::~PropertyTemplate() {}

	// -----  END  PropertyTemplate -----

	// ----- START PropertyGroupTemplate -----

	PropertyGroupTemplate::PropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate>& properties) :
		m_PropertyGroupTemplateId(id),
		m_PropertyGroupTemplateName(name),
		m_Properties(properties)
	{}

	PropertyGroupTemplate::~PropertyGroupTemplate() {}

	// ----  END  PropertyGroupTemplate -----

	// ----- START PropertyContainerTemplate -----

	PropertyContainerTemplate::PropertyContainerTemplate(uint32_t file_type_id, uint32_t usage, BufferPropertyTemplate<PropertyGroupTemplate>& groups) :
		m_PropertyContainerTemplateId(file_type_id),
		m_FileUsage(usage),
		m_Groups(groups)
	{}

	PropertyContainerTemplate::~PropertyContainerTemplate() {}

	// ----  END  PropertyContainerTemplate -----

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
		s_Instance->m_GroupTemplates[id] = groupTemplate;
		return groupTemplate;
	}

	PropertyContainerTemplate* PropertyManager::addPropertyContainerTemplate(uint32_t id, uint32_t type, BufferPropertyTemplate<PropertyGroupTemplate> groups) {
		if ((type == 0 && id < JPT_IO_PROPERTY_CONTAINER_IN_SIZE && s_Instance->m_ContainerTemplatesIn[id]) ||
			(type == 1 && id < JPT_IO_PROPERTY_CONTAINER_OUT_SIZE && s_Instance->m_ContainerTemplatesOut[id]))
			return type == 0 ? s_Instance->m_ContainerTemplatesIn[id] : s_Instance->m_ContainerTemplatesOut[id];

		PropertyContainerTemplate* containerTemplate = new PropertyContainerTemplate(id, type, groups);
		if (type == 0) s_Instance->m_ContainerTemplatesIn[id] = containerTemplate;
		else s_Instance->m_ContainerTemplatesOut[id] = containerTemplate;
		return containerTemplate;
	}

	PropertyBuffer PropertyManager::createPropertyBuffer(uint32_t file_input_type, uint32_t file_output_type) {
		return {};
	}

	// -----  END  PropertyManager -----
}