#pragma once
#ifdef JPT_ENABLE_OPENGL

#include "OpenGL.h"

#include "OpenGLRenderBuffers.hpp"
#include "OpenGLShader.hpp"
#include "OpenGLTexture.hpp"

namespace Jupiter::OpenGL {

	inline static void init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	inline static void setViewport(uint x, uint y, uint width, uint height) {
		glViewport(x, y, width, height);
	}

	inline static void setClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	inline static void clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	inline static void drawElements() {

	}

	inline static void drawArrays(uint first, uint size) {
		glDrawArrays(GL_TRIANGLES, first, size);
	}

//	inline static s_ptr<VertexArray> createVertexArray() {
//		return createShared<OpenGLVertexArray>();
//	}

	inline static s_ptr<VertexBuffer> createVertexBuffer(float* vertex_data, uint count, const VertexLayout& layout, VertexBufferSpecification& bufferSpec) {
		return createShared<OpenGLVertexBuffer>(vertex_data, count, layout, bufferSpec);
	}

	inline static s_ptr<IndexBuffer> createIndexBuffer(uint* index_data, uint count) {
		return createShared<OpenGLIndexBuffer>(index_data, count);
	}

	inline static s_ptr<Shader> createShader(ShaderLoadData& data) {
		return createShared<OpenGLShader>(data);
	}

	inline static s_ptr<Texture> createTexture2D(TextureSource& source, TextureSpecification& spec) {
		return createShared<OpenGLTexture2D>(source, spec);
	}

	inline static s_ptr<UniformBuffer> createUniformBuffer(uint size) {
		return createShared<OpenGLUniformBuffer>(size);
	}

}

#endif //  JPT_ENABLE_OPENGL
