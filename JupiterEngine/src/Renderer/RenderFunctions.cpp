#include "Renderer/RenderFunctions.h"

#ifdef JPT_ENABLE_OPENGL
#include "Platform/OpenGL/OpenGLRenderFunctions.hpp"
#endif

namespace Jupiter {

	void Jupiter::loadOpenGLBindings() {
#ifdef JPT_ENABLE_OPENGL
		s_JupiterRenderBoundFunctions->m_InitFunc = OpenGL::init;
		s_JupiterRenderBoundFunctions->m_SetViewportFunc = OpenGL::setViewport;
		s_JupiterRenderBoundFunctions->m_SetClearColorFunc = OpenGL::setClearColor;
		s_JupiterRenderBoundFunctions->m_ClearFunc = OpenGL::clear;
		s_JupiterRenderBoundFunctions->m_DrawElementsFunc = OpenGL::drawElements;
		s_JupiterRenderBoundFunctions->m_DrawArraysFunc = OpenGL::drawArrays;
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
