#pragma once

#include "Core.h"

#ifdef JPT_RENDER_BINDINGS_USE_DUMMY_BINDS
#define JPT_RENDER_BINDINGS_DUMMY_FUNC(x) x
#else
#define JPT_RENDER_BINDINGS_DUMMY_FUNC(x) nullptr
#endif // JPT_RENDER_BINDINGS_USE_DUMMY_BINDS

// #define jptr_Init() s_JupiterRenderBoundFunctions->m_InitFunc
// #define jptr_SetViewport(x, y, width, height) s_JupiterRenderBoundFunctions->m_SetViewportFunc(x, y, width, height)
// #define jptr_SetClearColor(r, g, b, a) s_JupiterRenderBoundFunctions->m_SetClearColorFunc(r, g, b, a)
// #define jptr_Clear() s_JupiterRenderBoundFunctions->m_ClearFunc()
// #define jptr_DrawElements() s_JupiterRenderBoundFunctions->m_DrawElementsFunc()
// #define jptr_DrawArrays() s_JupiterRenderBoundFunctions->m_DrawArraysFunc()
// #define jptr_CreateVertexArray() s_JupiterRenderBoundFunctions->m_CreateVertexArray()
// #define jptr_CreateVertexBuffer() s_JupiterRenderBoundFunctions->m_CreateVertexBuffer()

namespace Jupiter {

	// Function pointer definitions

	typedef void (*RenderFunc_Init)();
	typedef void (*RenderFunc_SetViewport)(uint x, uint y, uint width, uint height);
	typedef void (*RenderFunc_SetClearColor)(float r, float g, float b, float a);
	typedef void (*RenderFunc_Clear)();
	typedef void (*RenderFunc_DrawElements)();
	typedef void (*RenderFunc_DrawArrays)();
	// typedef void (*RenderFunc_CreateVertexArray)();
	// typedef void (*RenderFunc_CreateVertexBuffer)();

	/// <summary>
	/// Struct containing dummy functions that do nothing, makes sure that when no api has been bound the program does not crash
	/// </summary>
	struct GraphicsAPIDummy {
		static void dummyInit() {}
		static void dummySetViewport(uint x, uint y, uint width, uint height) {}
		static void dummySetClearColor(float r, float g, float b, float a) {}
		static void dummyClearFunc() {}
		static void dummyDrawElements() {}
		static void dummyDrawArrays() {}
		static void dummyCreateVertexArray() {}
		static void dummyCreateVertexBuffer() {}
	};

	/// <summary>
	/// struct containing pointers the graphics API specific functions
	/// </summary>
	struct RenderBoundFunctions {
		RenderFunc_Init m_InitFunc = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyInit);
		RenderFunc_SetViewport m_SetViewportFunc = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummySetViewport);
		RenderFunc_SetClearColor m_SetClearColorFunc = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummySetClearColor);
		RenderFunc_Clear m_ClearFunc = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyClearFunc);
		RenderFunc_DrawElements m_DrawElementsFunc = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyDrawElements);
		RenderFunc_DrawArrays m_DrawArraysFunc = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyDrawArrays);
		// RenderFunc_CreateVertexArray m_CreateVertexArray = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateVertexArray);
		// RenderFunc_CreateVertexBuffer m_CreateVertexBuffer = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateVertexBuffer);
	};

	/// <summary>
	/// struct mapping render constants to the graphics API specific value
	/// </summary>
	struct RendererConstants {

	};

	inline RenderBoundFunctions* s_JupiterRenderBoundFunctions = nullptr;

	namespace RenderFunctions {

		constexpr void init() { s_JupiterRenderBoundFunctions->m_InitFunc(); }
		constexpr void setViewport(int x, int y, int width, int height) { s_JupiterRenderBoundFunctions->m_SetViewportFunc(x, y, width, height); }
		constexpr void setClearColor(float r, float g, float b, float a) { s_JupiterRenderBoundFunctions->m_SetClearColorFunc(r, g, b, a); }
		constexpr void clear() { s_JupiterRenderBoundFunctions->m_ClearFunc(); }
		constexpr void drawElements() { s_JupiterRenderBoundFunctions->m_DrawElementsFunc(); }
		constexpr void drawArrays() { s_JupiterRenderBoundFunctions->m_DrawArraysFunc(); }

	}

	void loadOpenGLBindings();
	void loadDirectX11Bindings();
	void loadDirectX12Bindings();
	void loadVulkanBindings();
}
