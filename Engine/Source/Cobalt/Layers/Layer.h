#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	class Layer
	{
	public:
		Layer(const String& name = "Layer") : m_DebugName(name) {}
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiUpdate() {}
		virtual void OnEvent(Event& event) {}

		const String& GetName() const { return m_DebugName; }

	protected:
		String m_DebugName;
	};
}