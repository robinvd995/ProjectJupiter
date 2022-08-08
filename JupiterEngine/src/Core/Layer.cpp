#include "Core/Layer.h"

namespace Jupiter {

	// ----- START Layer -----

	Layer::Layer() {}

	Layer::~Layer() {}

	void Layer::onAdded() {}

	void Layer::onRemoved() {}

	void Layer::onUpdate() {}

	// -----  END  Layer -----


	// ----- START LayerList -----

	LayerList::LayerList() {

	}

	LayerList::~LayerList() {

	}

	void LayerList::add(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
		m_InsertIndex++;
	}

	void LayerList::addLast(Layer* layer) {
		m_Layers.emplace_back(m_Layers.end(), layer);
	}

	void LayerList::removeLayer(Layer* layer, bool isAddedLast) {
		auto found = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (found != m_Layers.end()) {
			m_Layers.erase(found);
			if (!isAddedLast) m_InsertIndex--;
		}
	}

	// -----  END  LayerList -----

}