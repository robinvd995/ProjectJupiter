#ifdef JPT_PLATFORM_WINDOWS
#pragma once

#include <GLFW/glfw3.h>

namespace Jupiter {

	class WindowsRenderContext {
	public:
		virtual void init(GLFWwindow* window_handle) = 0;
		virtual void swapBuffers(GLFWwindow* window_handle) = 0;
	};

	class WindowsOpenGLRenderContext : public WindowsRenderContext{
	public:
		virtual void init(GLFWwindow* window_handle) override;
		virtual void swapBuffers(GLFWwindow* window_handle) override;
	};

}

#endif
