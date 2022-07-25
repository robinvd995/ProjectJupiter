#pragma once

#include "Core.h"
#include "Core/Window.h"

namespace Jupiter {

	class Application {

	public:
		Application();
		~Application();

		void run();
		void closeApplication();

	private:
		Window* m_Window;
		bool m_Running;

	public:
		static Application* getInstance();
	private:
		static Application* s_Instance;
	};

	extern Application* createApplication();
}
