#pragma once
#ifdef JPT_ENABLE_OPENGL


#include "Renderer/GraphicsApi.h"
#include <glad/glad.h>

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

	inline static void drawArrays() {

	}

}

#endif //  JPT_ENABLE_OPENGL
