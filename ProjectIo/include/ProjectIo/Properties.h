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

	/// <summary>
	/// Buffer Property Template
	/// </summary>
	/// <typeparam name="T">The type of the values (I think)</typeparam>
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

	/// <summary>
	/// Index map for a property buffer
	/// </summary>
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

	/// <summary>
	/// Property Buffer
	/// </summary>
	class PropertyBuffer {

	public:
		PropertyBuffer() = delete;
		PropertyBuffer(const PropertyBuffer&) = delete;
		PropertyBuffer(PropertyBufferIndexMap* index_map);
		~PropertyBuffer();

		/// <summary>
		/// Sets the default value of a property
		/// </summary>
		/// <param name="group_id">The group id the property is part of</param>
		/// <param name="property_id">The id of the property</param>
		void setPropertyDefaultValue(uint32_t group_id, uint32_t property_id);

		/// <summary>
		/// Sets the value of the property
		/// </summary>
		/// <param name="group_id">The group id the property is part of</param>
		/// <param name="property_id">The id of the property</param>
		/// <param name="value">The value to set</param>
		void setPropertyValue(uint32_t group_id, uint32_t property_id, uint32_t value);

		/// <summary>
		/// Get the value of the given property from group
		/// </summary>
		/// <param name="group_id">The group id the property is part of</param>
		/// <param name="property_id">The id of the property</param>
		/// <returns></returns>
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

	/// <summary>
	/// 
	/// </summary>
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

	/// <summary>
	/// 
	/// </summary>
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

	/// <summary>
	/// 
	/// </summary>
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

	/// <summary>
	/// The property manager class
	/// </summary>
	class PropertyManager {

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="id"></param>
		/// <param name="name"></param>
		/// <returns></returns>
		static PropertyValueTemplate* addPropertyValueTemplate(uint32_t id, const std::string& name);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="id"></param>
		/// <param name="name"></param>
		/// <param name="accepted_values"></param>
		/// <returns></returns>
		static PropertyTemplate* addPropertyTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyValueTemplate> accepted_values);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="id"></param>
		/// <param name="name"></param>
		/// <param name="values"></param>
		/// <returns></returns>
		static PropertyGroupTemplate* addPropertyGroupTemplate(uint32_t id, const std::string& name, BufferPropertyTemplate<PropertyTemplate> values);
				
		/// <summary>
		/// 
		/// </summary>
		/// <param name="groups"></param>
		/// <returns></returns>
		static PropertyBufferIndexMap* createPropertyBufferIndexMap(const std::vector<PropertyGroupTemplate*>& groups);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="index_map"></param>
		/// <returns></returns>
		static PropertyBuffer* createPropertyBuffer(PropertyBufferIndexMap* index_map);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="buffer"></param>
		static void deletePropertyBuffer(PropertyBuffer* buffer);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="property_id"></param>
		/// <returns></returns>
		static uint32_t getDefaultValueForProperty(uint32_t property_id);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="property_template"></param>
		/// <returns></returns>
		static uint32_t getDefaultValueForProperty(PropertyTemplate* property_template);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="property_template"></param>
		/// <param name="value"></param>
		/// <returns></returns>
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
