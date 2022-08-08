#pragma once

#define JPT_IO_FILE_TYPE_INPUT_IDENTIFIER_PNG "png"
#define JPT_IO_FILE_TYPE_INPUT_IDENTIFIER_COLLADA "collada"

#define JPT_IO_FILE_TYPE_OUTPUT_IDENTIFIER_TEX_RGBA "tex_rgba"
#define JPT_IO_FILE_TYPE_OUTPUT_IDENTIFIER_MODEL_STATIC "model_static"

namespace Jupiter::Io {

	/// <summary>
	/// 
	/// </summary>
	enum EnumFileType {
		FILE_TYPE_UNDEFINED = 0,
		FILE_TYPE_PNG = 1,
		FILE_TYPE_COLLADA = 2,
		FILE_TYPE_GLSL = 3,


		ENUM_FILE_TYPE_COUNT
	};

}
