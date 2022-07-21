#pragma once

#include <string>
#include <vector>
#include <map>

#include "JupiterCore/DataBuffers.hpp"

#include "Core.h"

#include "PropertyDefinitions.h"

namespace Jupiter::Io {

	// [0] = group_id; [1] = index in buffer; [2] = size of group buffer
	typedef std::tuple<uint32_t, uint32_t, uint32_t> GroupIndex;
	// [0] = property_id; [1] = index of property local to group; [2] = size of property
	typedef std::tuple<uint32_t, uint32_t, uint32_t> PropertyIndex;
	// Typedef for the entries of the property index map
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

		const std::vector<T*>& getBuffer() const { return m_Buffer; }

	private:
		std::vector<T*> m_Buffer;

		friend class PropertyManager;
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)
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
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)
	};

	/*
		// TODO
	*/
	class PropertyBuffer {

	public:
		PropertyBuffer() = delete;
		PropertyBuffer(const PropertyBuffer&) = delete;
		PropertyBuffer(PropertyBufferIndexMap* index_map);
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
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)
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
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)
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

		const uint32_t getPropertyTemplateId() const;
		const std::string& getPropertyName() const;

	private:
		const uint32_t m_PropertyId;
		const std::string m_PropertyName;
		BufferPropertyTemplate<PropertyValueTemplate> m_AcceptedValues;
		uint32_t m_PropertyBufferSize;

		friend class PropertyManager;
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)
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

		const uint32_t getPropertyGroupTemplateId() const;
		const std::string& getPropertyGroupTemplateName() const;
		const std::vector<PropertyTemplate*>& getPropertyTemplates() const;

	private:
		const uint32_t m_PropertyGroupTemplateId;
		const std::string m_PropertyGroupTemplateName;
		BufferPropertyTemplate<PropertyTemplate> m_Properties;

		std::vector<PropertyIndex> m_PropertyIndicies;
		uint32_t m_PropertyGroupBufferSize = 0;

		friend class PropertyManager;
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)
	};

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
		static PropertyBufferIndexMap* createPropertyBufferIndexMap(const std::vector<PropertyGroupTemplate*>& groups);
		//TODO
		static PropertyBuffer* createPropertyBuffer(PropertyBufferIndexMap* index_map);
		//TODO
		static void deletePropertyBuffer(PropertyBuffer* buffer);

		//TODO
		static uint32_t getDefaultValueForProperty(uint32_t property_id);
		//TODO
		static uint32_t getDefaultValueForProperty(PropertyTemplate* property_template);
		//TODO
		static uint32_t getValueForPropertyAndValue(PropertyTemplate* property_template, const std::string& value);

	private:
		inline static PropertyManager* s_Instance = nullptr;
		friend class ProjectIo;
		JPT_IO_TEST_CLASS(PropertiesTestAdapter)

	private:
		PropertyManager();
		PropertyManager(const PropertyManager&) = delete;
		~PropertyManager();
		PropertyManager& operator=(const PropertyManager&) = delete;

	private:
		PropertyGroupTemplate* m_GroupTemplates[ENUM_PROPERTY_GROUPS_COUNT] = {};
		PropertyTemplate* m_PropertyTemplates[ENUM_PROPERTY_IDENTIFIERS_COUNT] = {};
		PropertyValueTemplate* m_ValueTemplates[ENUM_PROPERTY_VALUES_COUNT] = {};
	};
}
