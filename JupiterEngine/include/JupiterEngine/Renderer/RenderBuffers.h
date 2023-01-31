#pragma once

#include "JupiterCore/JupiterVertex.h"

namespace Jupiter {

//	class VertexArray {
//
//	public:
//		virtual ~VertexArray() {}
//
//		virtual void bind() const = 0;
//		virtual void unbind() const = 0;
//	};

	enum class BufferUsage {
		STATIC = 0,
		DYNAMIC = 1, 
		STREAM = 2
	};

	struct VertexBufferSpecification {
		const BufferUsage bufferUsage;

		VertexBufferSpecification() = delete;
		VertexBufferSpecification(BufferUsage usage);
	};

	class VertexBuffer {

	public:
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

//		virtual void setVertexLayout(const VertexLayout& layout) = 0;
		virtual void setIndexBuffer() = 0;
	};

	class IndexBuffer {

	public:
		virtual ~IndexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	};

}