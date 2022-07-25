#include "Application.h"

#include <iostream>

#include <Core/Input.h>

namespace Jupiter {

	Application* Application::s_Instance = nullptr;

	Application* Application::getInstance() { return s_Instance; }

	Application::Application() {
		s_Instance = this;
		Jupiter::Engine::initializeEngineLogger(0);

		uint windowFlags = JPT_ENGINE_WINDOW_FLAG_RESIZABLE | JPT_ENGINE_WINDOW_FLAG_VISIBLE | JPT_ENGINE_WINDOW_FLAG_DECORATED;
		m_Window = Window::createWindow("JupiterEngine", 1920, 1080, windowFlags);

		m_Running = true;
	}

	Application::~Application() {
		Jupiter::Engine::deleteLogger();
	}

	void Application::run() {
		while (m_Running) {
			m_Window->onUpdate();

			if (InputManager::isKeyPressed(EnumInputDevice::KEYBOARD, JPT_KEY_SPACE)) {
				JPT_ENGINE_INFO("KeyPressed =[0]", InputManager::isKeyPressed(EnumInputDevice::KEYBOARD, JPT_KEY_SPACE));
			}

			if (InputManager::isKeyReleased(EnumInputDevice::KEYBOARD, JPT_KEY_SPACE)) {
				JPT_ENGINE_INFO("KeyReleased =[0]", InputManager::isKeyReleased(EnumInputDevice::KEYBOARD, JPT_KEY_SPACE));
			}

			if (InputManager::isKeyDown(EnumInputDevice::KEYBOARD, JPT_KEY_W)) {
				JPT_ENGINE_INFO("KeyPressed =[0]", InputManager::isKeyPressed(EnumInputDevice::KEYBOARD, JPT_KEY_W));
			}

			if (m_Window->shouldWindowClose()) closeApplication();
		}
	}

	void Application::closeApplication() {
		m_Running = false;
	}
}
