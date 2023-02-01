#pragma once
#ifdef JPT_ENABLE_OPENGL

#include "OpenGL.h"

#include "JupiterEngine/Renderer/Texture.h"

namespace Jupiter {

	class OpenGLTexture2D : public Texture2D{

	public:
		OpenGLTexture2D() = delete;

		OpenGLTexture2D(TextureSource& source, TextureSpecification spec) {
			// Generate texture
			GLuint textureHandle;
			glGenTextures(1, &textureHandle);
			glBindTexture(GL_TEXTURE_2D, textureHandle);

			// Set texture wrapping/filter options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OpenGL::map_TextureWrapSpecification[(uint)spec.wrapS]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OpenGL::map_TextureWrapSpecification[(uint)spec.wrapT]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, OpenGL::map_TextureWrapSpecification[(uint)spec.wrapR]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OpenGL::map_TextureMinFilterSpecification[(uint)spec.minFilter]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OpenGL::map_TextureMinFilterSpecification[(uint)spec.magFilter]);

			// Load texture data
			glTexImage2D(GL_TEXTURE_2D, 0, OpenGL::map_TextureFormat[(uint)spec.format], source.textureWidth, 
				source.textureHeight, 0, GL_RGBA /*OpenGL::map_TextureFormat[(uint)source.format]*/, 
				GL_UNSIGNED_BYTE /*OpenGL::map_PrimitiveType[(uint)source.dataType]*/, source.textureData);

			m_TextureHandle = textureHandle;
			m_TextureWidth = source.textureWidth;
			m_TextureHeight = source.textureHeight;
		}

		virtual ~OpenGLTexture2D() override {
			glDeleteTextures(1, &m_TextureHandle);
		}

		virtual uint getWidth() const override {
			return m_TextureWidth;
		}

		virtual uint getHeight() const override {
			return m_TextureHeight;
		}

		virtual void bind() const override {
			glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
		}

	private:
		GLuint m_TextureHandle = 0;
		uint m_TextureWidth = 0;
		uint m_TextureHeight = 0;
	};
}

#endif