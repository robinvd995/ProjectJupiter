#pragma once

#include "Core.h"
#include "Core/Window.h"

namespace Jupiter {

	class JupiterEngineApplication {

	public:
		JupiterEngineApplication();
		~JupiterEngineApplication();

		/// <summary>
		/// Starts engine update loop
		/// </summary>
		void run();

		/// <summary>
		/// Flags the engine to stop running, doesnt actually shut down the application instantly
		/// </summary>
		void closeApplication();

	private:
		Window* m_Window;
		bool m_Running;

	public:
		/// <summary>
		/// Retrieves a pointer to the instance of the application
		/// </summary>
		/// <returns>Pointer to the instance of the application</returns>
		static JupiterEngineApplication* getInstance();
	private:
		static JupiterEngineApplication* s_Instance;
	};

	/// <summary>
	/// External function used to create the actual application
	/// Define this function in the project you want to create an instance of the engine in
	/// </summary>
	/// <returns>A new JupiterEngineApplication</returns>
	extern JupiterEngineApplication* createApplication();
}
