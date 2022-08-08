#pragma once

#include "GraphicsApi.h"
#include "Renderer/RenderBuffers.h"

namespace Jupiter {

	class RenderManager {

	public:
		static EnumGraphicsAPI getCurrentGraphicsAPI();
		static const RenderManager* getInstance();

	private:
		static void bindGraphicsAPI(EnumGraphicsAPI api);
		static void init();

		static RenderManager* s_Instance;

	private:
		RenderManager();
		RenderManager(const RenderManager&) = delete;
		~RenderManager();
		RenderManager& operator=(const RenderManager&) = delete;
		friend class JupiterEngineApplication;

	private:
		EnumGraphicsAPI m_GraphicsApi = EnumGraphicsAPI::NONE;
	};
}
