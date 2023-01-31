#pragma once

#include "JupiterDataTypes.h"

namespace Jupiter {

	/// <summary>
	/// The datatypes that are acceptable for an vertex
	/// </summary>
//	const JDataType* jVertexDataTypes[] = {
//		&JupiterDataTypes::type_vec3f, &JupiterDataTypes::type_vec4f
//	};

	/// <summary>
	/// 
	/// </summary>
	class VertexLayoutElement {

	public:
		VertexLayoutElement() = delete;
		VertexLayoutElement(const std::string& name, const JDataType* dataType, bool normalize = false);

		/// <summary>
		/// Gets the data type of the element
		/// </summary>
		/// <returns>data type as JDataType</returns>
		const JDataType& dataType() const;
		
		/// <summary>
		/// Gets the name for the element
		/// </summary>
		/// <returns>name as std::string</returns>
		const std::string name() const;
		
		/// <summary>
		/// Gets the offset of the element within the VertexLayout
		/// This will be calculated after the element has been added to a layout and the finalize function has been called
		/// </summary>
		/// <returns>the offset as uint</returns>
		uint offset() const;
		
		/// <summary>
		/// Gets if the data is normalized
		/// </summary>
		bool normalized() const;
		
		/// <summary>
		/// Gets the amount of components within the element data type
		/// </summary>
		/// <returns>the component count as uint</returns>
		uint componentCount() const;
		
		/// <summary>
		/// Returns the size of the element
		/// </summary>
		/// <returns>the size as uint</returns>
		uint size() const;

	private:
		const JDataType* m_DataType;
		char m_Name[32];
		uint m_NameLength;
		bool m_Normalized;
		uint m_Offset;
		uint m_Size;

		friend class VertexLayout;
	};

	/// <summary>
	/// 
	/// </summary>
	class VertexLayout {

	public:
		VertexLayout() = delete;
		VertexLayout(uint elementCount);
		~VertexLayout();

		/// <summary>
		/// 
		/// </summary>
		void addElement(uint position, VertexLayoutElement element);

		/// <summary>
		/// 
		/// </summary>
		void finalizeLayout();

		/// <summary>
		/// 
		/// </summary>
		uint getElementCount() const;

		/// <summary>
		/// 
		/// </summary>
		const VertexLayoutElement& getElement(uint location) const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		uint getStride() const;

	private:
		uint m_ElementCount;
		VertexLayoutElement* m_Elements;
		uint m_Stride;
	};

}
