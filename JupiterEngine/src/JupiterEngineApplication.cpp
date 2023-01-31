#include "JupiterEngine/JupiterEngineApplication.h"

#include "JupiterEngine/Core/Input.h"
#include "JupiterEngine/Core/Config.h"
#include "JupiterEngine/Core/TimeManager.h"

#include "JupiterEngine/Renderer/RenderManager.h"
#include "JupiterEngine/Renderer/RenderFunctions.h"

#include "JupiterEngine/Events/EventManager.h"
#include "JupiterEngine/Events/InitEvents.h"

#include "JupiterCore/JupiterTime.h"

namespace Jupiter {

	JupiterEngineApplication* JupiterEngineApplication::s_Instance = nullptr;

	JupiterEngineApplication* JupiterEngineApplication::getInstance() { return s_Instance; }

	JupiterEngineApplication::JupiterEngineApplication() {}

	JupiterEngineApplication::~JupiterEngineApplication() {
		delete ConfigManager::s_Instance; // Delete the config manager
		delete EventManager::s_Instance;  // Delete the event manager
		delete RenderManager::s_Instance; // Delete the render manager

		Jupiter::Engine::deleteLogger(); // Delete the engine logger
	}

	void JupiterEngineApplication::initEngine() {

		// Set application instance to current object
		s_Instance = this;

		// Initialize the logger
		Jupiter::Engine::initializeEngineLogger(m_JupiterLoggerFlags);

		// Initialize Event Systems
		EventManager::s_Instance = new EventManager();

		// Register engine events
//		EventManager::getEventHandler().registerEvent<EventInitConfig>();

		// Call to the application to register their events
		registerEvents();

		// Load config (Pseudo):
		//	- Initialize config manager
		//	- Post config init event (Config properties should be registered during this event)
		//	- Parse config file
		//	- Cleanup config manager

		ConfigManager::s_Instance = new ConfigManager();
		ConfigManager::loadPropertyBindings();

//		EventInitConfig initConfigEvent;
//		EventManager::getEventHandler().postEvent<EventInitConfig>(&initConfigEvent);

		// Call to the application to register their configuration options
		registerConfigOptions();

		ConfigContainer container;
		ConfigParser::loadConfigFile(container, m_ConfigFileName);

		ConfigManager::unloadPropertyBindings();

		// Initialize multithreading, Maybe after timesteps are initialized?

		// Initialize Time
		TimeManager::s_Instance = new TimeManager(m_FixedTimestep, m_MaxAllowedTimestep, m_ParticleTimestep);

		// Initialize the render engine
		RenderManager::s_Instance = new RenderManager();
		RenderManager::bindGraphicsAPI(EnumGraphicsAPI::OPEN_GL);

		// Initialize and create the window
		uint windowFlags = JPT_ENGINE_WINDOW_FLAG_RESIZABLE | JPT_ENGINE_WINDOW_FLAG_VISIBLE | JPT_ENGINE_WINDOW_FLAG_DECORATED;
		m_Window = Window::createWindow(m_ApplicationName, 1920, 1080, windowFlags);

		RenderFunctions::setViewport(0, 0, m_Window->getWindowWidth(), m_Window->getWindowHeight());
		RenderFunctions::setClearColor(1.0f, 1.0f, 0.0f, 1.0f);

		// Set the application status to running
		m_Running = true;
	}

	void JupiterEngineApplication::run() {
		// Call the init application for the application to initialize
		initApplication();

		double t = 0.0; // Time elapsed since the application has been running
		const double dt = TimeManager::s_Instance->m_TimeConstants.m_FixedTimestep; // The time it takes for 1 fixed timestep

		double currentTime = JTime::hiresTimeAsSeconds(); // The current time in seconds, gets updated every frame
		double accumulator = 0.0; // The accumalate of time that has passed since the simulation has been updated

		while (m_Running) {

			m_Window->onUpdate(); // update the window, also polls the input at this point in time
			RenderFunctions::clear(); // clears the window

			double newTime = JTime::hiresTimeAsSeconds(); // the new current time
			double frameTime = newTime - currentTime; // the time spend rendering the previous frame
			currentTime = newTime; // set the current time as the new time

			accumulator += frameTime; // Progress the accumulator by the amount of time spend rendering previous frame

			while (accumulator >= dt) {
				// Call fixed timestep
				for (auto it = m_LayerSet.m_Layers.begin(); it != m_LayerSet.m_Layers.end(); it++)
					it->m_Value->onFixedUpdate();

				// Decrease the accumulator amount by deltatime
				accumulator -= dt;

				// Increase the time passed by deltatime
				t += dt;
			}

			// Call update
			for (auto it = m_LayerSet.m_Layers.begin(); it != m_LayerSet.m_Layers.end(); it++)
				it->m_Value->onUpdate();

			// Call render
			// render stuff

			// If the window close has been called, stop the engine
			if (m_Window->shouldWindowClose()) stopEngine();
		}

		// Close application
		closeApplication();
	}

	void JupiterEngineApplication::stopEngine() {
		m_Running = false;
	}

	void JupiterEngineApplication::registerConfigOptions() {}
	void JupiterEngineApplication::registerEvents() {}

	LayerHandle JupiterEngineApplication::addLayer(LayerFactoryFunctor& layerfunctor, uint priority) {
		// Get the next available layer handle
		LayerHandle handle = m_LayerSet.getNextAvailableHandle();

		// Instantiate the layer object using the functor passed
		r_ptr<Layer> layer = layerfunctor();

		// Call the onAdded function in the layer
		layer->onAdded();

		// Add the layer to the LayerSet
		m_LayerSet.m_Layers.insert({ layer, priority, handle });

		// Return the handle for the layer
		return handle;
	}

	void JupiterEngineApplication::removeLayer(LayerHandle layerHandle) {
		// Loop trough the LayerSet to find a matching handle
		for (auto it = m_LayerSet.m_Layers.begin(); it != m_LayerSet.m_Layers.end(); it++) {

			// Check if handle matches
			if (it->m_Handle == layerHandle) {

				// Call onRemoved function in the layer
				it->m_Value->onRemoved();

				// Delete the instance of the layer
				delete it->m_Value;

				// Remove the layer from the set
				m_LayerSet.m_Layers.erase(it);
				break;
			}
		}
	}
}
