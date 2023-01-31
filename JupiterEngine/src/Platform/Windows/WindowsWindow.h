#ifdef JPT_PLATFORM_WINDOWS
#pragma once

#include "JupiterEngine/Core/Window.h"
#include "WindowsRenderContext.h"

namespace Jupiter {

	class WindowsWindow;

	struct WindowsWindowData {
		std::string m_WindowTitle = "WindowsWindowTitle";
		uint m_Width = 0;
		uint m_Height = 0;
		uint m_Flags = 0;
		bool m_ShouldClose = false;

		WindowsWindow* m_WindowInstance = nullptr;
	};

	class WindowsWindow : public Window {

	public:
		WindowsWindow() = delete;
		WindowsWindow(const std::string& title, uint width, uint height, uint flags);
		virtual ~WindowsWindow();

		virtual void onUpdate() override;
		virtual const uint getWindowWidth() const override;
		virtual const uint getWindowHeight() const override;
		virtual const bool shouldWindowClose() const override;

	private:
		void open();
		void close();

		void keyCallback(GLFWwindow* window_handle, int key, int scancode, int action, int mods);

	private:
		WindowsRenderContext* m_WindowRenderContext;
		GLFWwindow* m_WindowHandle;
		WindowsWindowData m_ActiveWindowData;
	};
}

#endif
