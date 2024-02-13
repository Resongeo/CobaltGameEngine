#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Layers/Layer.h"

namespace Cobalt
{
	class LayerStack
	{
	public:
		void PushLayer(Unique<Layer> layer);
		void PopLayer(Unique<Layer> layer);

		const Vector<Unique<Layer>>& GetLayers() const { return m_Layers; }

	private:
		Vector<Unique<Layer>> m_Layers;
	};
}

