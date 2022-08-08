#pragma once

#include "Core.h"

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	class Layer {

	public:
		Layer();
		virtual ~Layer();

		/// <summary>
		/// Called whenever the layer gets pushed to the stack
		/// </summary>
		virtual void onAdded();

		/// <summary>
		/// Called whenever the layer gets popper from the stack
		/// </summary>
		virtual void onRemoved();

		/// <summary>
		/// main update loop of the layer
		/// </summary>
		virtual void onUpdate();
	};

	/// <summary>
	/// Contains a collection of the current layers in the scene
	/// </summary>
	class LayerList {

	public:
		LayerList();
		~LayerList();

		/// <summary>
		/// Adds a layer to the list
		/// </summary>
		/// <param name="layer">Pointer to the layer to be added</param>
		void add(Layer* layer);

		/// <summary>
		/// Adds a layer to the list, will always remain at the end of the list
		/// </summary>
		/// <param name="layer">Pointer to the layer to be added</param>
		void addLast(Layer* layer);

		/// <summary>
		/// Removes a layer from the list
		/// </summary>
		/// <param name="layer">Pointer to the layer that has to be removed</param>
		/// <param name="isAddedLast">If the layer has been added trough the method addLast(Layer*) set this to true</param>
		void removeLayer(Layer* layer, bool isAddedLast);

	private:
		std::vector<Layer*> m_Layers;
		uint m_InsertIndex = 0;
	};

}
