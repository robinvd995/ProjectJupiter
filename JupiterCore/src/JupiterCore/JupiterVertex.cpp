#include "JupiterCore/JupiterVertex.h"

#include <iostream>

namespace Jupiter {

	VertexLayoutElement::VertexLayoutElement(const std::string& name, const JDataType* dataType, bool normalized) :
		m_DataType(dataType),
		m_Normalized(normalized),
		m_Offset(0)
	{
		m_Size = dataType->elements() * JupiterPrimitiveType_Size[(uint)dataType->primitive()];
		m_NameLength = name.size();

		JPT_ASSERT((m_NameLength < 32), "Name length cannot be larger then 32!");
		strcpy(&m_Name[0], name.c_str());
	}

	const JDataType& VertexLayoutElement::dataType() const {
		return *m_DataType;
	}

	const std::string VertexLayoutElement::name() const {
		return std::string(m_Name);
	}

	uint VertexLayoutElement::offset() const {
		return m_Offset;
	}

	bool VertexLayoutElement::normalized() const {
		return m_Normalized;
	}

	uint VertexLayoutElement::componentCount() const {
		return m_DataType->elements();
	}

	uint VertexLayoutElement::size() const {
		return m_DataType->size();
	}

	VertexLayout::VertexLayout(uint elementCount) :
		m_ElementCount(elementCount),
		m_Elements(nullptr),
		m_Stride(0)
	{
		m_Elements = (VertexLayoutElement*)malloc(sizeof(VertexLayoutElement) * m_ElementCount);
	}

	VertexLayout::~VertexLayout() {
		free(m_Elements);
	}

	void VertexLayout::addElement(uint position, VertexLayoutElement element) {
		JPT_ASSERT((position < m_ElementCount), "Position is larger then element count!");
		m_Elements[position] = element;
	}

	void VertexLayout::finalizeLayout() {
		uint offset = 0;
		for (int i = 0; i < m_ElementCount; i++) {
			VertexLayoutElement& element = m_Elements[i];
			element.m_Offset = offset;
			offset += element.size();
		}
		m_Stride = offset;
	}

	uint VertexLayout::getElementCount() const {
		return m_ElementCount;
	}

	const VertexLayoutElement& VertexLayout::getElement(uint location) const {
		JPT_ASSERT((location < m_ElementCount), "Location is larger than element count!");
		return m_Elements[location];
	}

	uint VertexLayout::getStride() const {
		return m_Stride;
	}
}