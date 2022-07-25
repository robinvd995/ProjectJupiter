#ifdef JPT_PLATFORM_WINDOWS

#include "WindowsWindow.h"
#include "Core/Input.h"

#include <GLFW/glfw3.h>

namespace Jupiter {

	static bool s_GlfwInitialized = false;

	void glfwErrorCallback(int error, const char* message) {
		JPT_ENGINE_ERROR("GLFW error: [0]: [1]", error, message);
	}

	void glfwWindowCloseCallback(GLFWwindow* window_handle) {
		WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window_handle);
		data.m_ShouldClose = true;
	}

	void glfwWindowSizeCallback(GLFWwindow* window_handle, int width, int height) {
		WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window_handle);
		data.m_Width = width;
		data.m_Height = height;
	}

	Window* Jupiter::Window::createWindow(const std::string& title, uint width, uint height, uint flags) {
		return new WindowsWindow(title, width, height, flags);
	}

	WindowsWindow::WindowsWindow(const std::string& title, uint width, uint height, uint flags) {
		m_ActiveWindowData.m_WindowTitle = title;
		m_ActiveWindowData.m_Width = width;
		m_ActiveWindowData.m_Height = height;
		m_ActiveWindowData.m_WindowInstance = this;
		m_ActiveWindowData.m_Flags = flags;

		open();
	}

	WindowsWindow::~WindowsWindow() {
		close();
	}

	void WindowsWindow::onUpdate() {
		m_WindowRenderContext->swapBuffers(m_WindowHandle);
		InputManager::updateInputs({ EnumInputDevice::KEYBOARD, EnumInputDevice::MOUSE });
		glfwPollEvents();
	}

	const uint WindowsWindow::getWindowWidth() const {
		return m_ActiveWindowData.m_Width;
	}

	const uint WindowsWindow::getWindowHeight() const {
		return m_ActiveWindowData.m_Height;
	}

	const bool Jupiter::WindowsWindow::shouldWindowClose() const {
		return m_ActiveWindowData.m_ShouldClose;
	}

	void WindowsWindow::open() {
		if (!s_GlfwInitialized) {
			int success = glfwInit();
			glfwSetErrorCallback(glfwErrorCallback);
			s_GlfwInitialized = true;
		}

		// WINDOW CREATION HINTS
		glfwWindowHint(GLFW_RESIZABLE, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_RESIZABLE);
		glfwWindowHint(GLFW_VISIBLE, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_VISIBLE);
		glfwWindowHint(GLFW_DECORATED, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_DECORATED);
		glfwWindowHint(GLFW_FOCUSED, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_FOCUSED);
		glfwWindowHint(GLFW_AUTO_ICONIFY, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_AUTO_ICONIFY);
		glfwWindowHint(GLFW_FLOATING, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_FLOATING);
		glfwWindowHint(GLFW_MAXIMIZED, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_MAXIMIZED);
		glfwWindowHint(GLFW_CENTER_CURSOR, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_CENTER_CURSOR);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_TRANSPARENT_FRAMBEBUFFER);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_FOCUS_ON_SHOW);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, m_ActiveWindowData.m_Flags & JPT_ENGINE_WINDOW_FLAG_SCALE_TO_MONITOR);

		m_WindowHandle = glfwCreateWindow(m_ActiveWindowData.m_Width, m_ActiveWindowData.m_Height,
			m_ActiveWindowData.m_WindowTitle.c_str(), nullptr, nullptr);

		m_WindowRenderContext = new WindowsOpenGLRenderContext();
		m_WindowRenderContext->init(m_WindowHandle);

		glfwSetWindowUserPointer(m_WindowHandle, &m_ActiveWindowData);

		// CALLBACK FUNCTIONS
		glfwSetWindowCloseCallback(m_WindowHandle, glfwWindowCloseCallback);
		glfwSetWindowSizeCallback(m_WindowHandle, glfwWindowSizeCallback);

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window_handle, int key, int scancode, int action, int mods) {
			WindowsWindowData& data = *(WindowsWindowData*)glfwGetWindowUserPointer(window_handle);
			data.m_WindowInstance->keyCallback(window_handle, key, scancode, action, mods);
		});

		InputManager::s_Instance = new InputManager();
		InputManager::s_Instance->m_KeyStateRegistries[(uint)EnumInputDevice::KEYBOARD].addTrackedKeys({ JPT_KEY_SPACE });
	}

	void WindowsWindow::close() {
		delete m_WindowRenderContext;
		delete InputManager::s_Instance;
	}

	void WindowsWindow::keyCallback(GLFWwindow* window_handle, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) InputManager::onKeyStateChanged(EnumInputDevice::KEYBOARD, key, true);
		else if (action == GLFW_RELEASE) InputManager::onKeyStateChanged(EnumInputDevice::KEYBOARD, key, false);
	}
}

#endif
