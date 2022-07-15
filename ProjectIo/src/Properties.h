#pragma once

#include <string>
#include <vector>

#define JPT_IO_PROPERTY_GROUPS_SIZE 3				// TODO
#define JPT_IO_PROPERTY_IDENTIFIERS_SIZE 6			// TODO
#define JPT_IO_PROPERTY_VALUES_SIZE 12				// TODO
#define JPT_IO_PROPERTY_CONTAINER_IN_SIZE 4			// TODO
#define JPT_IO_PROPERTY_CONTAINER_OUT_SIZE 4		// TODO

namespace Jupiter::Io {

	/*
		// TODO
	*/
	template<typename T>
	struct BufferPropertyTemplate {

	public:
		BufferPropertyTemplate() {}
		template<typename T>
		BufferPropertyTemplate(const std::initializer_list<T*>& values) : m_Buffer(values) {}
		~BufferPropertyTemplate() {}

	private:
		std::vector<T*> m_Buffer;

	};

	/*
		// TODO
	*/
	struct PropertyValueTemplate {

	public:
		PropertyValueTemplate() = delete;
		PropertyValueTemplate(PropertyValueTemplate&) = delete;
		PropertyValueTemplate(uint32_t id, const std::string& name);
		~PropertyValueTemplate();

	private:
		const uint32_t m_PropertyValueId;
		const std::string m_PropertyValueName;

		friend class PropertyManager;
	};

	/*
		// TODO
	*/
	struct PropertyTemplate {

	public:
		PropertyTemplate() = delete;
		PropertyTemplate(PropertyTemplate&) = delete;
		PropertyTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyValueTemplate>& accepted_values);
		~PropertyTemplate();

	private:
		const uint32_t m_PropertyId;
		const std::string m_PropertyName;
		BufferPropertyTemplate<PropertyValueTemplate> m_AcceptedValues;

		friend class PropertyManager;
	};

	/*
		// TODO
	*/
	struct PropertyGroupTemplate {

	public:
		PropertyGroupTemplate() = delete;
		PropertyGroupTemplate(PropertyTemplate&) = delete;
		PropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate>& accepted_values);
		~PropertyGroupTemplate();

	private:
		const uint32_t m_PropertyGroupTemplateId;
		const std::string m_PropertyGroupTemplateName;
		BufferPropertyTemplate<PropertyTemplate> m_Properties;

		friend class PropertyManager;
	};

	/*
		// TODO
	*/
	struct PropertyContainerTemplate {

	public:
		PropertyContainerTemplate() = delete;
		PropertyContainerTemplate(PropertyContainerTemplate&) = delete;
		PropertyContainerTemplate(uint32_t file_type_id, uint32_t usage, BufferPropertyTemplate<PropertyGroupTemplate>& groups);
		~PropertyContainerTemplate();

	private:
		const uint32_t m_PropertyContainerTemplateId;
		const uint32_t m_FileUsage; // 0 = input, 1 = output
		BufferPropertyTemplate<PropertyGroupTemplate>& m_Groups;

		friend class PropertyManager;
	};

	/*
		// TODO
	*/
	class PropertyBuffer {

	public:

	private:

	};
	
	/*
		// TODO	
	*/
	class PropertyManager {

	public:
		//TODO
		static PropertyValueTemplate* addPropertyValueTemplate(uint32_t id, const std::string& name);
		//TODO
		static PropertyTemplate* addPropertyTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyValueTemplate> accepted_values);
		//TODO
		static PropertyGroupTemplate* addPropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate> values);
		//TODO
		static PropertyContainerTemplate* addPropertyContainerTemplate(uint32_t id, uint32_t type, BufferPropertyTemplate<PropertyGroupTemplate> group);
		//TODO
		static PropertyBuffer createPropertyBuffer(uint32_t file_input_type, uint32_t file_output_type);

	private:
		inline static PropertyManager* s_Instance = nullptr;
		friend class ProjectIo;

	private:
		PropertyManager();
		PropertyManager(PropertyManager&) = delete;
		~PropertyManager();

	private:
		PropertyGroupTemplate* m_GroupTemplates[JPT_IO_PROPERTY_GROUPS_SIZE] = {};
		PropertyTemplate* m_PropertyTemplates[JPT_IO_PROPERTY_IDENTIFIERS_SIZE] = {};
		PropertyValueTemplate* m_ValueTemplates[JPT_IO_PROPERTY_VALUES_SIZE] = {};
		PropertyContainerTemplate* m_ContainerTemplatesIn[JPT_IO_PROPERTY_CONTAINER_IN_SIZE] = {};
		PropertyContainerTemplate* m_ContainerTemplatesOut[JPT_IO_PROPERTY_CONTAINER_OUT_SIZE] = {};
	};
}
