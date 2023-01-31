#pragma once

#include "JupiterCore.h"
#include "JupiterCoreDefinitions.h"

namespace Jupiter {

	/// <summary>
	/// Enum containing the primitive data types
	/// </summary>
	enum class JupiterPrimitiveType {
		CHAR = 0,
		UCHAR = 1,
		SHORT = 2,
		USHORT = 3,
		INT = 4,
		UINT = 5,
		FLOAT = 6,
		DOUBLE = 7,
		BOOL = 8
	};

	/// <summary>
	/// Size of the primitive datatypes declared in enum class JupiterPrimitiveType
	/// </summary>
	const uint JupiterPrimitiveType_Size[]{
		1,		// JupiterPrimitiveType::CHAR (0)
		1,		// JupiterPrimitiveType::CHAR (1)
		2,		// JupiterPrimitiveType::SHORT (2)
		2,		// JupiterPrimitiveType::USHORT (3)
		4,		// JupiterPrimitiveType::INT (4)
		4,		// JupiterPrimitiveType::UINT (5)
		4,		// JupiterPrimitiveType::FLOAT (6)
		4,		// JupiterPrimitiveType::DOUBLE (7)
		4,		// JupiterPrimitiveType::BOOL (8)
	};

	/// <summary>
	/// Representation of the differnt data types used
	/// </summary>
	class JDataType {

	public:
		// Deleted constructors
		JDataType() = delete;
		JDataType(const JDataType&) = delete;

		JDataType(const std::string& name, const std::string& identifier, uint elements, JupiterPrimitiveType primitiveType);

		/// <summary>
		/// Retrieves the name of the data type
		/// </summary>
		/// <returns></returns>
		const std::string& name() const;

		/// <summary>
		/// Retrieves the identifier of the data type
		/// </summary>
		/// <returns></returns>
		const std::string& identifier() const;

		/// <summary>
		/// returns the size of the datatype in bytes
		/// </summary>
		/// <returns></returns>
		uint size() const;

		/// <summary>
		/// Returns the amount of primitive elements this type contains
		/// </summary>
		/// <returns></returns>
		uint elements() const;

		/// <summary>
		/// Returns the enum type of the primitive data type
		/// </summary>
		/// <returns></returns>
		JupiterPrimitiveType primitive() const;

	private:
		const std::string m_Name;
		const std::string m_Identifier;
		uint m_Size;
		const uint m_Elements;
		const JupiterPrimitiveType m_PrimitiveType;
	};

	/// <summary>
	/// Collection class
	/// </summary>
	class JupiterDataTypes {

	public:
		// Primitive data type representations
		static const JDataType type_Char, type_Short, type_UShort, type_Int, type_UInt, type_float, type_double, type_bool;

		// Vector data type representations
		static const JDataType type_vec2f, type_vec2i, type_vec3f, type_vec3i, type_vec4f, type_vec4i;

		// Matrix data type representations
		static const JDataType type_mat44f, type_mat33f;
	};
}
