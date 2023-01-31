#include "JupiterEngine/Renderer/RenderManager.h"

#include "JupiterEngine/Renderer/RenderFunctions.h"

#ifdef JPT_ENABLE_OPENGL
#include "Platform/OpenGL/OpenGLRenderFunctions.hpp"
#endif

namespace Jupiter {

	RenderManager* RenderManager::s_Instance = nullptr;

	RenderManager::RenderManager() {}

	RenderManager::~RenderManager() {
		delete s_JupiterRenderBoundFunctions;
	}

	void RenderManager::bindGraphicsAPI(EnumGraphicsAPI api) {

		s_JupiterRenderBoundFunctions = new RenderBoundFunctions();

		switch (api) {

		case EnumGraphicsAPI::NONE:
			JPT_ENGINE_ERROR("Render API 'NONE' is currently not supported on the current platform!");
			break;

		case EnumGraphicsAPI::OPEN_GL:
#ifdef JPT_ENABLE_OPENGL
			loadOpenGLBindings();
#else
			JPT_ENGINE_ERROR("Render API 'OPEN_GL' is currently not supported on the current platform!");
#endif
			break;
		case EnumGraphicsAPI::DIRECTX11:
			JPT_ENGINE_ERROR("Render API 'DIRECTX11' is currently not supported on the current platform!");
			break;

		case EnumGraphicsAPI::DIRECTX12:
			JPT_ENGINE_ERROR("Render API 'DIRECTX12' is currently not supported on the current platform!");
			break;

		case EnumGraphicsAPI::VULKAN:
			JPT_ENGINE_ERROR("Render API 'VULKAN' is currently not supported on the current platform!");
			break;
		}
		s_Instance->m_GraphicsApi = api;
	}

	void RenderManager::init() {
		// s_Instance->m_GraphicsAPIFunctions.m_InitFunc();


	}

	EnumGraphicsAPI RenderManager::getCurrentGraphicsAPI() {
		return s_Instance->m_GraphicsApi;
	}
	
	const RenderManager* RenderManager::getInstance() {
		return s_Instance;
	}

}
