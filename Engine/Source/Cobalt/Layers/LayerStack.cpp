#include "cbpch.h"

#include "Cobalt/Layers/LayerStack.h"

namespace Cobalt
{
	void LayerStack::PushLayer(Unique<Layer> layer)
	{
		m_Layers.push_back(std::move(layer));
	}

	void LayerStack::PopLayer(Unique<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			Unique<Layer> foundLayer = std::move(*it);
			m_Layers.erase(it);
		}
	}
}