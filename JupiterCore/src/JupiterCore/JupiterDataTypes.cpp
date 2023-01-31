#include "JupiterCore/JupiterDataTypes.h"

namespace Jupiter {

	JDataType::JDataType(const std::string& name, const std::string& identifier, uint elements, JupiterPrimitiveType primitiveType) :
		m_Name(name),
		m_Identifier(identifier),
		m_Elements(elements),
		m_PrimitiveType(primitiveType)
	{
		m_Size = m_Elements * JupiterPrimitiveType_Size[(uint)primitiveType];
	}

	const std::string& JDataType::name() const {
		return m_Name;
	}

	const std::string& JDataType::identifier() const {
		return m_Identifier;
	}

	uint JDataType::size() const {
		return m_Size;
	}

	uint JDataType::elements() const {
		return m_Elements;
	}

	JupiterPrimitiveType JDataType::primitive() const {
		return m_PrimitiveType;
	}

	// ----- Primitive definitions -----
	const JDataType JupiterDataTypes::type_Char("Char", "char", 1, JupiterPrimitiveType::CHAR);
	const JDataType JupiterDataTypes::type_Short("Short", "short", 1, JupiterPrimitiveType::SHORT);
	const JDataType JupiterDataTypes::type_UShort("UShort", "Ushort", 1, JupiterPrimitiveType::USHORT);
	const JDataType JupiterDataTypes::type_Int("Integer", "int", 1, JupiterPrimitiveType::INT);
	const JDataType JupiterDataTypes::type_UInt("Unsigned Integer", "uint", 1, JupiterPrimitiveType::UINT);
	const JDataType JupiterDataTypes::type_float("Float", "float", 1, JupiterPrimitiveType::FLOAT);
	const JDataType JupiterDataTypes::type_double("Double", "double", 1, JupiterPrimitiveType::DOUBLE);
	const JDataType JupiterDataTypes::type_bool("Boolean", "bool", 1, JupiterPrimitiveType::BOOL);

	// ----- Vector definitions -----
	const JDataType JupiterDataTypes::type_vec2f("Vector 2f", "vec2", 2, JupiterPrimitiveType::FLOAT);
	const JDataType JupiterDataTypes::type_vec2i("Vector 2i", "vec2i", 2, JupiterPrimitiveType::INT);
	const JDataType JupiterDataTypes::type_vec3f("Vector 3f", "vec3", 3, JupiterPrimitiveType::FLOAT);
	const JDataType JupiterDataTypes::type_vec3i("Vector 3i", "vec3i", 3, JupiterPrimitiveType::INT);
	const JDataType JupiterDataTypes::type_vec4f("Vector 4f", "vec4", 4, JupiterPrimitiveType::FLOAT);
	const JDataType JupiterDataTypes::type_vec4i("Vector 4i", "vec4i", 4, JupiterPrimitiveType::INT);

	// ----- Matrix definitions -----
	const JDataType JupiterDataTypes::type_mat44f("Matrix 4f", "mat4", 16, JupiterPrimitiveType::FLOAT);
	const JDataType JupiterDataTypes::type_mat33f("Matrix 3f", "mat3", 9, JupiterPrimitiveType::FLOAT);
}