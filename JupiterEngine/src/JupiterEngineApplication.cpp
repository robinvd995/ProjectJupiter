#include "JupiterEngineApplication.h"

#include "Renderer/RenderManager.h"
#include "Renderer/RenderFunctions.h"
#include "Core/Input.h"

namespace Jupiter {

	JupiterEngineApplication* JupiterEngineApplication::s_Instance = nullptr;

	JupiterEngineApplication* JupiterEngineApplication::getInstance() { return s_Instance; }

	JupiterEngineApplication::JupiterEngineApplication() {
		s_Instance = this;
		Jupiter::Engine::initializeEngineLogger(0);

		RenderManager::s_Instance = new RenderManager();
		RenderManager::bindGraphicsAPI(EnumGraphicsAPI::OPEN_GL);

		uint windowFlags = JPT_ENGINE_WINDOW_FLAG_RESIZABLE | JPT_ENGINE_WINDOW_FLAG_VISIBLE | JPT_ENGINE_WINDOW_FLAG_DECORATED;
		m_Window = Window::createWindow("JupiterEngine", 1920, 1080, windowFlags);

		RenderFunctions::setViewport(0, 0, m_Window->getWindowWidth(), m_Window->getWindowHeight());
		RenderFunctions::setClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		m_Running = true;
	}

	JupiterEngineApplication::~JupiterEngineApplication() {
		delete RenderManager::s_Instance;

		Jupiter::Engine::deleteLogger();
	}

	void JupiterEngineApplication::run() {
		while (m_Running) {
			m_Window->onUpdate();

			RenderFunctions::clear();


			if (m_Window->shouldWindowClose()) closeApplication();
		}
	}

	void JupiterEngineApplication::closeApplication() {
		m_Running = false;
	}
}
