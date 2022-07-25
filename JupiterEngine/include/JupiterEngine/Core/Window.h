#pragma once

#include "Core.h"

#include <string>

#define JPT_ENGINE_WINDOW_FLAG_RESIZABLE					1
#define JPT_ENGINE_WINDOW_FLAG_VISIBLE						2
#define JPT_ENGINE_WINDOW_FLAG_DECORATED					4
#define JPT_ENGINE_WINDOW_FLAG_FOCUSED						8
#define JPT_ENGINE_WINDOW_FLAG_AUTO_ICONIFY					16
#define JPT_ENGINE_WINDOW_FLAG_FLOATING						32
#define JPT_ENGINE_WINDOW_FLAG_MAXIMIZED					64
#define JPT_ENGINE_WINDOW_FLAG_CENTER_CURSOR				128
#define JPT_ENGINE_WINDOW_FLAG_TRANSPARENT_FRAMBEBUFFER		256
#define JPT_ENGINE_WINDOW_FLAG_FOCUS_ON_SHOW				512
#define JPT_ENGINE_WINDOW_FLAG_SCALE_TO_MONITOR				1024
#define JPT_ENGINE_WINDOW_FLAG_VSYNC						2048

namespace Jupiter {

//	struct WindowProperties {
//		const std::string m_WindowTitle;
//		const uint m_WindowWidth;
//		const uint m_WindowHeight;
//		const uint m_WindowFlags;
//
//		WindowProperties(const std::string& title, uint width, uint height, uint flags) :
//			m_WindowTitle(title), m_WindowWidth(width), m_WindowHeight(height), m_WindowFlags(flags)
//		{}
//	};

	class Window {

	public:
		virtual ~Window() {}

		virtual void onUpdate() = 0;
		virtual const uint getWindowWidth() const = 0;
		virtual const uint getWindowHeight() const = 0;
		virtual const bool shouldWindowClose() const = 0;

		static Window* createWindow(const std::string& title, uint width, uint height, uint flags);
		// static Window* createWindow(const WindowProperties& window_properties);
	};

}
