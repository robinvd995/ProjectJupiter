#pragma once

#include "JupiterEngine/JupiterEngineApplication.h"
#include "JunoLayer.hpp"

namespace Juno {

	class JunoLayerFunctor : public Jupiter::LayerFactoryFunctor {

	public:
		JunoLayerFunctor(const std::string& layername) :
			m_LayerName(layername)
		{}

		virtual Jupiter::r_ptr<Jupiter::Layer> operator()() override {
			return Jupiter::createRaw<JunoLayer>(m_LayerName);
		}

	private:
		std::string m_LayerName;
	};

	class JunoApplication : public Jupiter::JupiterEngineApplication {

	public:
		JunoApplication() {
			m_JupiterLoggerFlags = 1;
			m_ConfigFileName = "test.cfg";
			m_ApplicationName = "Sandbox Juno";
		}
		~JunoApplication() {}

		virtual void initApplication() override {
			JunoLayerFunctor functor0("Layer 0");

			m_LayerHandle0 = addLayer(functor0, 3);
		}

		virtual void closeApplication() override {
			removeLayer(m_LayerHandle0);
		}

		void registerConfigOptions() override {
			JPT_ENGINE_INFO("Register Config Options");
		}

		void registerEvents() override {
			JPT_ENGINE_INFO("Register Events");
		}

	private:
		Jupiter::LayerHandle m_LayerHandle0;
	};

}

