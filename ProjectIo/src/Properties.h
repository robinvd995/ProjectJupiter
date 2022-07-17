#pragma once

#include <string>
#include <vector>
#include <map>

#include "JupiterCore/DataBuffers.hpp"

#define JPT_IO_PROPERTY_GROUPS_SIZE 3				// TODO
#define JPT_IO_PROPERTY_IDENTIFIERS_SIZE 6			// TODO
#define JPT_IO_PROPERTY_VALUES_SIZE 12				// TODO
#define JPT_IO_PROPERTY_CONTAINER_SIZE 4			// TODO

namespace Jupiter::Io {

	// [0] = group_id; [1] = index in buffer; [2] = size of group buffer
	typedef std::tuple<uint32_t, uint32_t, uint32_t> GroupIndex;
	// [0] = property_id; [1] = index of property local to group; [2] = size of property
	typedef std::tuple<uint32_t, uint32_t, uint32_t> PropertyIndex;

	typedef std::pair<GroupIndex, std::vector<PropertyIndex>> PropertyIndexMapEntry;

	// ---- BUFFERS -----

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

		friend class PropertyManager;
	};

	class PropertyBufferIndexMap {

	public:
		PropertyBufferIndexMap();
		PropertyBufferIndexMap(const PropertyBufferIndexMap&) = delete;
		~PropertyBufferIndexMap();

	private:
		uint32_t m_BufferSize;
		std::vector<PropertyIndexMapEntry> m_IndexMap;

		friend class PropertyManager;
		friend class PropertyBuffer;
	};

	/*
		// TODO
	*/
	class PropertyBuffer {

	public:
		PropertyBuffer() = delete;
		PropertyBuffer(PropertyBufferIndexMap* index_map);
		PropertyBuffer(const PropertyBuffer&) = delete;
		~PropertyBuffer();

		void setPropertyDefaultValue(uint32_t group_id, uint32_t property_id);
		void setPropertyValue(uint32_t group_id, uint32_t property_id, uint32_t value);
		uint32_t getPropertyValue(uint32_t group_id, uint32_t property_id);

	private:
		bool moveIterator(uint32_t group_id, uint32_t property_id);

	private:
		Core::ByteBuffer m_Buffer;
		PropertyBufferIndexMap* m_IndexMap = nullptr;

		friend class PropertyManager;
	};

	// ----- TEMPLATES -----

	/*
		// TODO
	*/
	struct PropertyValueTemplate {

	public:
		PropertyValueTemplate() = delete;
		PropertyValueTemplate(const PropertyValueTemplate&) = delete;
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
		PropertyTemplate(const PropertyTemplate&) = delete;
		PropertyTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyValueTemplate>& accepted_values);
		~PropertyTemplate();

	private:
		const uint32_t m_PropertyId;
		const std::string m_PropertyName;
		BufferPropertyTemplate<PropertyValueTemplate> m_AcceptedValues;
		uint32_t m_PropertyBufferSize;

		friend class PropertyManager;
	};

	/*
		// TODO
	*/
	struct PropertyGroupTemplate {

	public:
		PropertyGroupTemplate() = delete;
		PropertyGroupTemplate(const PropertyTemplate&) = delete;
		PropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate>& accepted_values);
		~PropertyGroupTemplate();

	private:
		const uint32_t m_PropertyGroupTemplateId;
		const std::string m_PropertyGroupTemplateName;
		BufferPropertyTemplate<PropertyTemplate> m_Properties;

		std::vector<PropertyIndex> m_PropertyIndicies;
		uint32_t m_PropertyGroupBufferSize = 0;

		friend class PropertyManager;
	};

	/*
		// TODO
	*/
	/*struct PropertyContainerTemplate {

	public:
		PropertyContainerTemplate() = delete;
		PropertyContainerTemplate(const PropertyContainerTemplate&) = delete;
		PropertyContainerTemplate(uint32_t file_type_id, uint32_t usage, BufferPropertyTemplate<PropertyGroupTemplate>& groups);
		~PropertyContainerTemplate();

	private:
		const uint32_t m_PropertyContainerTemplateId;
		const uint32_t m_FileUsage;
		BufferPropertyTemplate<PropertyGroupTemplate>& m_Groups;

		friend class PropertyManager;
	};*/
	
	// ----- MANAGER -----

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
		//static PropertyContainerTemplate* addPropertyContainerTemplate(uint32_t file_type_id, uint32_t usage, BufferPropertyTemplate<PropertyGroupTemplate> group);
		
		//TODO
		static PropertyBufferIndexMap* createPropertyBufferIndexMap(std::initializer_list<uint32_t> group_ids);
		//TODO
		static PropertyBuffer* createPropertyBuffer(PropertyBufferIndexMap* index_map);

		//TODO
		static uint32_t getDefaultValueForProperty(uint32_t property_id);

	private:
		inline static PropertyManager* s_Instance = nullptr;
		friend class ProjectIo;

	private:
		PropertyManager();
		PropertyManager(const PropertyManager&) = delete;
		~PropertyManager();
		PropertyManager& operator=(const PropertyManager&) = delete;

	private:
		PropertyGroupTemplate* m_GroupTemplates[JPT_IO_PROPERTY_GROUPS_SIZE] = {};
		PropertyTemplate* m_PropertyTemplates[JPT_IO_PROPERTY_IDENTIFIERS_SIZE] = {};
		PropertyValueTemplate* m_ValueTemplates[JPT_IO_PROPERTY_VALUES_SIZE] = {};
		//PropertyContainerTemplate* m_ContainerTemplates[JPT_IO_PROPERTY_CONTAINER_SIZE] = {};
	};
}
