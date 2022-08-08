#pragma once
#ifdef JPT_ENABLE_OPENGL
#include "Renderer/RenderBuffers.h"

#include "Core.h"

#include <glad/glad.h>

namespace Jupiter {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertex_data, uint count) {
			glGenBuffers(1, &m_BufferHandle);
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertex_data, GL_STATIC_DRAW);
		}

		virtual ~OpenGLVertexBuffer() {
			glDeleteBuffers(1, &m_BufferHandle);
		}

		virtual void bind() const override {
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle);
		}

		virtual void unbind() const override {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	private:
		uint m_BufferHandle = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer {

		OpenGLIndexBuffer(uint* indices, uint count)  :
			m_IndicesCount(count)
		{
			glGenBuffers(1, &m_BufferHandle);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferHandle);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * count, indices, GL_STATIC_DRAW);
		}

		virtual ~OpenGLIndexBuffer() {
			glDeleteBuffers(1, &m_BufferHandle);
		}

		virtual void bind() const override {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferHandle);
		}

		virtual void unbind() const override {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	private:
		uint m_BufferHandle = 0;
		uint m_IndicesCount = 0;

	};

}


#endif
