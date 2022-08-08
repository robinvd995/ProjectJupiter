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

		/// <summary>
		/// Updates the window
		/// </summary>
		virtual void onUpdate() = 0;

		/// <summary>
		/// Retrieves the width of the window
		/// </summary>
		/// <returns>The window width in pixels</returns>
		virtual const uint getWindowWidth() const = 0;

		/// <summary>
		/// Retrieves the height of the window
		/// </summary>
		/// <returns>The window height in pixels</returns>
		virtual const uint getWindowHeight() const = 0;

		/// <summary>
		/// Retrieves the window should be closing or not
		/// </summary>
		/// <returns>true if window should close</returns>
		virtual const bool shouldWindowClose() const = 0;

		/// <summary>
		/// Creates the window
		/// </summary>
		/// <param name="title">The title of the window</param>
		/// <param name="width">Window width in pixels</param>
		/// <param name="height">Window height in pixels</param>
		/// <param name="flags">Window creation hints/flags that need to be passed during the creation</param>
		/// <returns></returns>
		static Window* createWindow(const std::string& title, uint width, uint height, uint flags);
	};

}
