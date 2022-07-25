#ifdef JPT_PLATFORM_WINDOWS
#include "WindowsRenderContext.h"

#include <Core.h>
#include <glad/glad.h>

namespace Jupiter {

	void WindowsOpenGLRenderContext::init(GLFWwindow* window_handle) {
		glfwMakeContextCurrent(window_handle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JPT_ASSERT(gladStatus, "Unable to load glad!");
		JPT_ENGINE_INFO("OpenGL [0] loaded", glGetString(GL_VERSION));
	}

	void WindowsOpenGLRenderContext::swapBuffers(GLFWwindow* window_handle) {
		glfwSwapBuffers(window_handle);
	}

}

#endif
