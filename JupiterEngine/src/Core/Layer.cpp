#include "JupiterEngine/Core/Layer.h"

namespace Jupiter {

	LayerSetEntry::LayerSetEntry(r_ptr<Layer> v, uint p, LayerHandle h) :
		m_Value(v), m_Priority(p), m_Handle(h)
	{}

	bool LayerSetEntry::operator<(const LayerSetEntry& other) const {
		return m_Priority > other.m_Priority;
	}

	bool LayerSetEntry::operator==(const LayerSetEntry& other) const {
		return m_Handle == other.m_Handle;
	}

//	LayerHandle LayerSet::addLayer(LayerFactoryFunctor& layer, uint priority) {
//		LayerHandle handle = getNextAvailableHandle();
//		//m_Layers.insert({ layer, priority, handle });
//		m_LayerHandles.push_back(handle);
//		return handle;
//	}

//	r_ptr<Layer> Jupiter::LayerSet::removeLayer(LayerHandle layerhandle) {
//		LayerSetEntry lse(nullptr, 0, layerhandle);
//		auto it = m_Layers.find(lse);
//		if (it != m_Layers.end()) {
//			r_ptr<Layer> val = it->m_Value;
//			m_LayerHandles.erase(std::find(m_LayerHandles.begin(), m_LayerHandles.end(), layerhandle));
//			m_Layers.erase(it);
//			return val;
//		}
//	}

	LayerHandle LayerSet::getNextAvailableHandle() {
		LayerHandle handle = m_NextHandle++;
		return handle;
	}
}
