#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Layers/Layer.h"

namespace Cobalt
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		Vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		Vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		Vector<Layer*> m_Layers;
		Vector<Layer*>::iterator m_LayerInsert;
	};
}

