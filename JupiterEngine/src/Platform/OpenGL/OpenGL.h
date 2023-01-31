#pragma once

#ifdef JPT_ENABLE_OPENGL

#include "JupiterEngine/JupiterEngine.h"
#include <glad/glad.h>

namespace Jupiter::OpenGL {
	
	inline GLuint map_BufferUsage[] = {
		GL_STATIC_DRAW,		// BufferUsage::STATIC
		GL_DYNAMIC_DRAW,	// BufferUsage::DYNAMIC
		GL_STREAM_DRAW		// BufferUsage::STREAM
	};

	inline GLuint map_PrimitiveType[] = {
		GL_BYTE,			// JupiterPrimitiveType::CHAR (0)
		GL_UNSIGNED_BYTE,	// JupiterPrimitiveType::CHAR (1)
		GL_SHORT,			// JupiterPrimitiveType::SHORT (2)
		GL_UNSIGNED_SHORT,	// JupiterPrimitiveType::USHORT (3)
		GL_INT,				// JupiterPrimitiveType::INT (4)
		GL_UNSIGNED_INT,	// JupiterPrimitiveType::UINT (5)
		GL_FLOAT,			// JupiterPrimitiveType::FLOAT (6)
		GL_DOUBLE,			// JupiterPrimitiveType::DOUBLE (7)
		GL_BOOL,			// JupiterPrimitiveType::BOOL (8)
	};
}

#endif
