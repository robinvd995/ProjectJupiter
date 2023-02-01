#pragma once

#ifdef JPT_ENABLE_OPENGL

#include "JupiterEngine/JupiterEngine.h"
#include <glad/glad.h>

namespace Jupiter::OpenGL {
	
	inline GLuint map_BufferUsage[] = {
		GL_STATIC_DRAW,					// (0) BufferUsage::STATIC
		GL_DYNAMIC_DRAW,				// (1) BufferUsage::DYNAMIC
		GL_STREAM_DRAW					// (2) BufferUsage::STREAM
	};

	inline GLuint map_PrimitiveType[] = {
		GL_BYTE,						// (0) JupiterPrimitiveType::CHAR
		GL_UNSIGNED_BYTE,				// (1) JupiterPrimitiveType::UCHAR
		GL_SHORT,						// (2) JupiterPrimitiveType::SHORT
		GL_UNSIGNED_SHORT,				// (3) JupiterPrimitiveType::USHORT
		GL_INT,							// (4) JupiterPrimitiveType::INT
		GL_UNSIGNED_INT,				// (5) JupiterPrimitiveType::UINT
		GL_FLOAT,						// (6) JupiterPrimitiveType::FLOAT
		GL_DOUBLE,						// (7) JupiterPrimitiveType::DOUBLE
		GL_BOOL,						// (8) JupiterPrimitiveType::BOOL
	};

	inline GLuint map_TextureFormat[] = {
		GL_RGBA,						// (0) TextureFormat::RGBA
		GL_RGB,							// (1) TextureFormat::RGB
	};

	inline GLuint map_TextureMinFilterSpecification[] = {
		GL_LINEAR,						// (0) TextureMinFilterSpecification::Linear
		GL_NEAREST,						// (1) TextureMinFilterSpecification::Nearest
		GL_NEAREST_MIPMAP_NEAREST,		// (2) TextureMinFilterSpecification::NearestMipmapNearest
		GL_LINEAR_MIPMAP_NEAREST,		// (3) TextureMinFilterSpecification::LinearMipmapNearest
		GL_NEAREST_MIPMAP_LINEAR,		// (4) TextureMinFilterSpecification::NearestMipmapLinear
		GL_LINEAR_MIPMAP_LINEAR,		// (5) TextureMinFilterSpecification::LinearMipmapLinear
	};

	inline GLuint map_TextureMagFilterSpecification[] = {
		GL_LINEAR,						// (0) TextureMagFilterSpecification::Linear
		GL_NEAREST,						// (1) TextureMagFilterSpecification::Nearest
	};

	inline GLuint map_TextureWrapSpecification[] = {
		GL_REPEAT,						// (0) TextureWrapSpecification::Repeat
		GL_CLAMP_TO_EDGE,				// (1) TextureWrapSpecification::ClampToEdge
		GL_CLAMP_TO_BORDER,				// (2) TextureWrapSpecification::ClampToBorder
		GL_MIRRORED_REPEAT,				// (3) TextureWrapSpecification::MirroredRepeat
		GL_MIRROR_CLAMP_TO_EDGE,		// (4) TextureWrapSpecification::MirroredClampToEdge
	};
}

#endif
