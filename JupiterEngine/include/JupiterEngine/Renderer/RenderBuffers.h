#pragma once

namespace Jupiter {

	class VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};

	class VertexBuffer {

	public:
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};

	class IndexBuffer {

	public:
		virtual ~IndexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	};

}