#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	class EditorPanel
	{
	public:
		virtual void OnLoad() { }
		virtual void OnUpdate() { }
		virtual void OnUIRender() { }
		virtual void OnEvent(Event& event) { }
	};
}