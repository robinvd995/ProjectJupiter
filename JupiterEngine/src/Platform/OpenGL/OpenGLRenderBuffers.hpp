#pragma once
#ifdef JPT_ENABLE_OPENGL

#include "OpenGL.h"

#include "JupiterEngine/Renderer/RenderBuffers.h"

namespace Jupiter {

//	class OpenGLVertexArray : public VertexArray {
//
//	public:
//		virtual ~OpenGLVertexArray() override {
//			
//		}
//
//		virtual void bind() const override {
//			
//		}
//
//		virtual void unbind() const override {
//			
//		}
//	};

	/// <summary>
	/// OpenGL representation of an IndexBuffer object
	/// </summary>
	class OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(uint* indices, uint count) :
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

	/// <summary>
	/// OpenGL representation of an VertexBuffer object
	/// </summary>
	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertex_data, uint count, const VertexLayout& layout, VertexBufferSpecification& bufferSpec) {
			// Generate vertex array
			glGenVertexArrays(1, &m_VertexArrayHandle);
			glBindVertexArray(m_VertexArrayHandle);

			// Generate vertex buffer
			glGenBuffers(1, &m_BufferHandle);
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle);

			// Set buffer data
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertex_data, OpenGL::map_BufferUsage[(uint)bufferSpec.bufferUsage]);

			JPT_ASSERT((layout.getElementCount() > 0), "Vertex Layout has not specified elements!");

			// Iterate trough the elements withing the layout
			for (int i = 0; i < layout.getElementCount(); i++) {
				VertexLayoutElement element = layout.getElement(i);

				// Enable the attributes and bind them
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.componentCount(), OpenGL::map_PrimitiveType[(uint)element.dataType().primitive()], 
					element.normalized(), layout.getStride(), (const void*)element.offset());
			}
		}

		virtual ~OpenGLVertexBuffer() {
			glDeleteBuffers(1, &m_BufferHandle);
		}

		virtual void bind() const override {
			glBindVertexArray(m_VertexArrayHandle);
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle);
		}

		virtual void unbind() const override {
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

//		virtual void setVertexLayout(const VertexLayout& layout) override {
//			JPT_ASSERT((layout.getElementCount() > 0), "Vertex Layout has not specified elements!");
//
//			for (int i = 0; i < layout.getElementCount(); i++) {
//				VertexLayoutElement element = layout.getElement(i);
//				glEnableVertexAttribArray(i);
//				glVertexAttribPointer(i, element.componentCount(), GL_FLOAT, element.normalized(), 
//					layout.getStride(), (const void*)element.offset());
//			}
//		}

		virtual void setIndexBuffer() override {

		}

	private:
		uint m_VertexArrayHandle = 0;
		uint m_BufferHandle = 0;
	};

	class OpenGLUniformBuffer : public UniformBuffer {

	public:
		OpenGLUniformBuffer(const uint size) : 
			c_BufferSize(size)
		{
			glGenBuffers(1, &m_BufferHandle);
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle);
			glBufferData(GL_UNIFORM_BUFFER, size, NULL, OpenGL::map_BufferUsage[(uint)BufferUsage::DYNAMIC]);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		virtual ~OpenGLUniformBuffer() override {
			glDeleteBuffers(1, &m_BufferHandle);
		}

		virtual void bind(uint bufferbinding) override {
			glBindBufferRange(GL_UNIFORM_BUFFER, bufferbinding, m_BufferHandle, 0, c_BufferSize);
		}

		virtual void bufferData(const char* data) override {
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, c_BufferSize, data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		virtual void bufferData(const uint offset, const uint size, const char* data) override {
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle);
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

	private:
		const GLsizeiptr c_BufferSize;
		GLuint m_BufferHandle;
	};
}


#endif
