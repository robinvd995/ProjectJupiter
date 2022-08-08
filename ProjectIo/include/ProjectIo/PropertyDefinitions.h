#pragma once

namespace Jupiter::Io {

	/// <summary>
	/// Enum containing all the property groups
	/// </summary>
	enum EnumPropertyGroups {
		PG_UNDEFINED = 0,

		PG_GROUP_TEXTURE = 1,
		PG_GROUP_MODEL = 2,


		ENUM_PROPERTY_GROUPS_COUNT
	};

	/// <summary>
	/// Enum containing all the property identifiers
	/// </summary>
	enum EnumPropertyIdentifiers {
		PI_UNDEFINED = 0,

		// ----- Texture ----- 
		PI_TEXTURE_MIN_FILTER = 1,
		PI_TEXTURE_MAG_FILTER = 2,
		PI_TEXTURE_WRAP_S = 3,
		PI_TEXTURE_WRAP_T = 4,
		PI_TEXTURE_WRAP_R = 5,


		ENUM_PROPERTY_IDENTIFIERS_COUNT
	};

	/// <summary>
	/// Enum containing all the property values
	/// </summary>
	enum EnumPropertyValues {
		PV_UNDEFINED = 0,

		// ----- General -----
		PV_FALSE = 12,
		PV_TRUE = 13,

		// ----- Texture -----
		PV_TEXTURE_NEAREST = 1,
		PV_TEXTURE_LINEAR = 2,
		PV_TEXTURE_NEAREST_MIPMAP_NEAREST = 3,
		PV_TEXTURE_LINEAR_MIPMAP_NEAREST = 4,
		PV_TEXTURE_NEAREST_MIPMAP_LINEAR = 5,
		PV_TEXTURE_LINEAR_MIPMAP_LINEAR = 6,
		PV_TEXTURE_REPEAT = 7,
		PV_TEXTURE_CLAMP_TO_EDGE = 8,
		PV_TEXTURE_CLAMP_TO_BORDER = 9,
		PV_TEXTURE_MIRRORED_REPEAT = 10,
		PV_TEXTURE_MIRRORED_CLAMP_TO_EDGE = 11,

		ENUM_PROPERTY_VALUES_COUNT
	};
}
