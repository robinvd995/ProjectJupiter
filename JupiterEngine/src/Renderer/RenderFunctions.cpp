#include "JupiterEngine/Renderer/RenderFunctions.h"

#ifdef JPT_ENABLE_OPENGL
#include "Platform/OpenGL/OpenGLRenderFunctions.hpp"
#endif

namespace Jupiter {

	// Dummy functions
	void GraphicsAPIDummy::dummyInit() { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
	}

	void GraphicsAPIDummy::dummySetViewport(uint x, uint y, uint width, uint height) { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
	}

	void GraphicsAPIDummy::dummySetClearColor(float r, float g, float b, float a) { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
	}

	void GraphicsAPIDummy::dummyClearFunc() { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
	}

	void GraphicsAPIDummy::dummyDrawElements() { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
	}

	void GraphicsAPIDummy::dummyDrawArrays(uint first, uint size) {
		JPT_ASSERT_FAIL("Graphics API function is not bound!");
	}

//	s_ptr<VertexArray> GraphicsAPIDummy::dummyCreateVertexArray() { 
//		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
//		return nullptr; 
//	}

	r_ptr<VertexBuffer> GraphicsAPIDummy::dummyCreateVertexBuffer(float*, uint, const VertexLayout&, VertexBufferSpecification&) {
		JPT_ASSERT_FAIL("Graphics API function is not bound!");
		return nullptr;
	}

	r_ptr<IndexBuffer> GraphicsAPIDummy::dummyCreateIndexBuffer(uint*, uint) { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!"); 
		return nullptr; 
	}

	r_ptr<Shader> GraphicsAPIDummy::dummyCreateShader(ShaderLoadData& data) { 
		JPT_ASSERT_FAIL("Graphics API function is not bound!");
		return nullptr; 
	}

	r_ptr<Texture> GraphicsAPIDummy::dummyCreateTexture(TextureSource& source, TextureSpecification& spec) {
		JPT_ASSERT_FAIL("Graphics API function is not bound!");
		return nullptr;
	}

	r_ptr<UniformBuffer> GraphicsAPIDummy::dummyCreateUniformBuffer(uint size) {
		JPT_ASSERT_FAIL("Graphics API function is not bound!");
		return nullptr;
	}

	// Common functions
	void RenderFunctions::init() { 
		s_JupiterRenderBoundFunctions->m_InitFunc(); 
	}

	void RenderFunctions::clear() { 
		s_JupiterRenderBoundFunctions->m_ClearFunc(); 
	}

	// Set functions
	void RenderFunctions::setViewport(int x, int y, int width, int height) { 
		s_JupiterRenderBoundFunctions->m_SetViewportFunc(x, y, width, height); 
	}

	void RenderFunctions::setClearColor(float r, float g, float b, float a) { 
		s_JupiterRenderBoundFunctions->m_SetClearColorFunc(r, g, b, a); 
	}

	// Draw functions
	void RenderFunctions::drawElements() { 
		s_JupiterRenderBoundFunctions->m_DrawElementsFunc(); 
	}

	void RenderFunctions::drawArrays(uint first, uint size) {
		s_JupiterRenderBoundFunctions->m_DrawArraysFunc(first, size); 
	}

	// Create functions
//	s_ptr<VertexArray> RenderFunctions::createVertexArray() { 
//		return s_JupiterRenderBoundFunctions->m_CreateVertexArray(); 
//	}

	r_ptr<VertexBuffer> RenderFunctions::createVertexBuffer(float* vertex_data, uint count, const VertexLayout& layout, VertexBufferSpecification bufferSpec) {
		return s_JupiterRenderBoundFunctions->m_CreateVertexBuffer(vertex_data, count, layout, bufferSpec);
	}

	r_ptr<IndexBuffer> RenderFunctions::createIndexBuffer(uint* index_data, uint count) { 
		return s_JupiterRenderBoundFunctions->m_CreateIndexBuffer(index_data, count); 
	}

	r_ptr<Shader> RenderFunctions::createShader(ShaderLoadData& data) { 
		return s_JupiterRenderBoundFunctions->m_CreateShader(data); 
	}

	r_ptr<Texture> RenderFunctions::createTexture2D(TextureSource& source, TextureSpecification& spec) {
		return s_JupiterRenderBoundFunctions->m_CreateTexture2D(source, spec);
	}

	r_ptr<UniformBuffer> RenderFunctions::createUniformBuffer(uint size) {
		return s_JupiterRenderBoundFunctions->m_CreateUniformBuffer(size);
	}

	// Load bindings
	void Jupiter::loadOpenGLBindings() {
#ifdef JPT_ENABLE_OPENGL
		s_JupiterRenderBoundFunctions->m_InitFunc = OpenGL::init;
		s_JupiterRenderBoundFunctions->m_SetViewportFunc = OpenGL::setViewport;
		s_JupiterRenderBoundFunctions->m_SetClearColorFunc = OpenGL::setClearColor;
		s_JupiterRenderBoundFunctions->m_ClearFunc = OpenGL::clear;
		s_JupiterRenderBoundFunctions->m_DrawElementsFunc = OpenGL::drawElements;
		s_JupiterRenderBoundFunctions->m_DrawArraysFunc = OpenGL::drawArrays;
//		s_JupiterRenderBoundFunctions->m_CreateVertexArray = OpenGL::createVertexArray;
		s_JupiterRenderBoundFunctions->m_CreateVertexBuffer = OpenGL::createVertexBuffer;
		s_JupiterRenderBoundFunctions->m_CreateIndexBuffer = OpenGL::createIndexBuffer;
		s_JupiterRenderBoundFunctions->m_CreateShader = OpenGL::createShader;
		s_JupiterRenderBoundFunctions->m_CreateTexture2D = OpenGL::createTexture2D;
		s_JupiterRenderBoundFunctions->m_CreateUniformBuffer = OpenGL::createUniformBuffer;
#else
		JPT_ENGINE_ERROR("Trying to load OpenGL bindings while OpenGL is not available in this build!");
#endif
	}

	void loadDirectX11Bindings() {
#ifdef JPT_ENABLE_DIRECTX11

#else
		JPT_ENGINE_ERROR("Trying to load DirectX11 bindings while DirectX11 is not available in this build!");
#endif
	}

	void loadDirectX12Bindings() {
#ifdef JPT_ENABLE_DIRECTX12

#else
		JPT_ENGINE_ERROR("Trying to load DirectX12 bindings while DirectX12 is not available in this build!");
#endif
	}

	void loadVulkanBindings() {
#ifdef JPT_ENABLE_VULKAN

#else
		JPT_ENGINE_ERROR("Trying to load Vulkan bindings while Vulkan is not available in this build!");
#endif
	}
}
