#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include "Shader.h"
#include "RenderBuffers.h"
#include "Texture.h"

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
	typedef void (*RenderFunc_DrawArrays)(uint first, uint size);
//	typedef s_ptr<VertexArray> (*RenderFunc_CreateVertexArray)();
	typedef s_ptr<VertexBuffer> (*RenderFunc_CreateVertexBuffer)(float* vertex_data, uint count, const VertexLayout& layout, VertexBufferSpecification& bufferSpec);
	typedef s_ptr<IndexBuffer> (*RenderFunc_CreateIndexBuffer)(uint* vertex_data, uint count);
	typedef s_ptr<Shader>(*RenderFunc_CreateShader)(ShaderLoadData& data);
	typedef s_ptr<Texture>(*RenderFunc_CreateTexture)(TextureSource& source, TextureSpecification& spec);
	typedef s_ptr<UniformBuffer>(*RenderFunc_CreateUniformBuffer)(uint size);

	/// <summary>
	/// Struct containing dummy functions that do nothing, makes sure that when no api has been bound the program does not crash
	/// </summary>
	struct GraphicsAPIDummy {
		static void dummyInit();
		static void dummySetViewport(uint x, uint y, uint width, uint height);
		static void dummySetClearColor(float r, float g, float b, float a);
		static void dummyClearFunc();
		static void dummyDrawElements();
		static void dummyDrawArrays(uint first, uint size);
//		static s_ptr<VertexArray> dummyCreateVertexArray();
		static s_ptr<VertexBuffer> dummyCreateVertexBuffer(float*, uint, const VertexLayout&, VertexBufferSpecification&);
		static s_ptr<IndexBuffer> dummyCreateIndexBuffer(uint*, uint);
		static s_ptr<Shader> dummyCreateShader(ShaderLoadData& data);
		static s_ptr<Texture> dummyCreateTexture(TextureSource& source, TextureSpecification& spec);
		static s_ptr<UniformBuffer> dummyCreateUniformBuffer(uint);
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
//		RenderFunc_CreateVertexArray m_CreateVertexArray = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateVertexArray);
		RenderFunc_CreateVertexBuffer m_CreateVertexBuffer = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateVertexBuffer);
		RenderFunc_CreateIndexBuffer m_CreateIndexBuffer = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateIndexBuffer);
		RenderFunc_CreateShader m_CreateShader = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateShader);
		RenderFunc_CreateTexture m_CreateTexture2D = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateTexture);
		RenderFunc_CreateUniformBuffer m_CreateUniformBuffer = JPT_RENDER_BINDINGS_DUMMY_FUNC(GraphicsAPIDummy::dummyCreateUniformBuffer);
	};

	/// <summary>
	/// struct mapping render constants to the graphics API specific value
	/// </summary>
	struct RendererConstants {

	};

	inline RenderBoundFunctions* s_JupiterRenderBoundFunctions = nullptr;

	/// <summary>
	/// Namespace containing the render functions used in the engine
	/// </summary>
	namespace RenderFunctions {
		// ----- Common functions -----

		/// <summary>
		/// 
		/// </summary>
		void init();

		/// <summary>
		/// 
		/// </summary>
		void clear();
		
		// ----- Set functions ----- 

		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void setViewport(int x, int y, int width, int height);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		/// <param name="a"></param>
		void setClearColor(float r, float g, float b, float a);
		
		// ----- Draw functions -----

		/// <summary>
		/// 
		/// </summary>
		void drawElements();

		/// <summary>
		/// 
		/// </summary>
		void drawArrays(uint first, uint size);

		// ----- Create functions ----- 

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
//		s_ptr<VertexArray> createVertexArray();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="vertex_data"></param>
		/// <param name="count"></param>
		/// <param name="layout"></param>
		/// <param name="bufferSpec"></param>
		/// <returns></returns>
		s_ptr<VertexBuffer> createVertexBuffer(float* vertex_data, uint count, const VertexLayout& layout, VertexBufferSpecification bufferSpec);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="index_data"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		s_ptr<IndexBuffer> createIndexBuffer(uint* index_data, uint count);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		s_ptr<Shader> createShader(ShaderLoadData& data);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="source"></param>
		/// <param name="spec"></param>
		/// <returns></returns>
		s_ptr<Texture> createTexture2D(TextureSource& source, TextureSpecification& spec);

		s_ptr<UniformBuffer> createUniformBuffer(uint size);
	}

	/// <summary>
	/// Sets the function bindings to the OpenGL bindings
	/// </summary>
	void loadOpenGLBindings();

	/// <summary>
	/// Sets the function bindings to the DirectX11 bindings
	/// </summary>
	void loadDirectX11Bindings();

	/// <summary>
	/// Sets the function bindings to the DirectX12 bindings
	/// </summary>
	void loadDirectX12Bindings();

	/// <summary>
	/// Sets the function bindings to the Vulkan bindings
	/// </summary>
	void loadVulkanBindings();
}
