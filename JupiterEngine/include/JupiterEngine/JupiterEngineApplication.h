#pragma once

#include "JupiterEngine.h"

#include "Core/Layer.h"
#include "Core/Window.h"

namespace Jupiter {

	class JupiterEngineApplication {

	public:
		JupiterEngineApplication();
		~JupiterEngineApplication();

		/// <summary>
		/// Initializes the engine
		/// </summary>
		void initEngine();

		/// <summary>
		/// Starts engine update loop
		/// </summary>
		void run();

		/// <summary>
		/// Flags the engine to stop running, doesnt actually shut down the engine instantly
		/// </summary>
		void stopEngine();

	protected:
		/// <summary>
		/// Flags used to initialize the engine logger
		/// </summary>
		l_uint m_JupiterLoggerFlags = 0;

		/// <summary>
		/// The name of the config file
		/// </summary>
		std::string m_ConfigFileName = "jconfig.cfg";

		/// <summary>
		/// The name of the application as seen on the window
		/// </summary>
		std::string m_ApplicationName = "JupiterEngine App";

		/// <summary>
		/// How many times per second the fixed timestep is called for eg. physics
		/// </summary>
		double m_FixedTimestep = 60.0;

		/// <summary>
		/// The minimum amount of times the simulation must be updated
		/// </summary>
		double m_MaxAllowedTimestep = 10.0;

		/// <summary>
		/// How often the particles are updated per second
		/// </summary>
		double m_ParticleTimestep = 30.0;

	protected:
		/// <summary>
		/// Function called at the start of the run function
		/// Most of the initialization of the application should take place here, eg. adding layers etc.
		/// </summary>
		virtual void initApplication() = 0;

		/// <summary>
		/// Function called at the end of the run function
		/// Used mostly to release memory and cleanup
		/// </summary>
		virtual void closeApplication() = 0;

		/// <summary>
		/// 
		/// </summary>
		virtual void registerConfigOptions();

		/// <summary>
		/// 
		/// </summary>
		virtual void registerEvents();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="layer"></param>
		/// <param name="priority"></param>
		/// <return>layer handle</return>
		LayerHandle addLayer(LayerFactoryFunctor& layerfunctor, uint priority = 0);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="layerHandle"></param>
		void removeLayer(LayerHandle layerHandle);

	private:
		Window* m_Window = nullptr;
		bool m_Running = false;
		LayerSet m_LayerSet;

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
