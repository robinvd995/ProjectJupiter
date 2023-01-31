#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include <set>

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	class Layer {

	public:
		virtual ~Layer() {};

		/// <summary>
		/// Called whenever the layer gets pushed to the stack
		/// </summary>
		virtual void onAdded() = 0;

		/// <summary>
		/// Called whenever the layer gets popped from the stack
		/// </summary>
		virtual void onRemoved() = 0;

		/// <summary>
		/// Update loop with an fluid timestep
		/// </summary>
		virtual void onUpdate() = 0;

		/// <summary>
		/// Update loop with a fixed timestep
		/// </summary>
		virtual void onFixedUpdate() = 0;
	};

	typedef uint LayerHandle;

	/// <summary>
	/// Entry struct for the LayerSet class
	/// </summary>
	struct LayerSetEntry {
		const r_ptr<Layer> m_Value = nullptr;
		const uint m_Priority = 0;

		LayerHandle m_Handle;

		LayerSetEntry() = delete;
		LayerSetEntry(r_ptr<Layer> v, uint p, LayerHandle h);

		bool operator < (const LayerSetEntry& other) const;
		bool operator ==(const LayerSetEntry& other) const;
	};

	/// <summary>
	/// Functor
	/// </summary>
	class LayerFactoryFunctor {
	
	public:
		virtual r_ptr<Layer> operator()() = 0;
	};

	/// <summary>
	/// Contains a collection of the current layers
	/// </summary>
	class LayerSet {

	public:
		LayerSet() = default;
		~LayerSet() = default;

		/// <summary>
		/// Adds a layer to the application
		/// </summary>
		/// <param name="layer">Pointer to the layer object</param>
		/// <param name="priority">Determines the position in the LayerSet, higher priority means earlier in the set</param>
		/// <returns>The layer handle used to further interact with the layer</returns>
//		LayerHandle addLayer(LayerFactoryFunctor& factoryfunctor, uint priority);

		/// <summary>
		/// Removes a layer from the set
		/// </summary>
		/// <param name="layerhandle">The layerhandle of the layer wanting to be removed</param>
//		r_ptr<Layer> removeLayer(LayerHandle layerhandle);

	private:
		/// <summary>
		/// Gets the next available handle
		/// </summary>
		/// <returns>The next available handle</returns>
		LayerHandle getNextAvailableHandle();

	private:
		std::set<LayerSetEntry> m_Layers;
		// std::vector<LayerHandle> m_LayerHandles;

		uint m_NextHandle = 0;

		friend class JupiterEngineApplication;
	};

}
