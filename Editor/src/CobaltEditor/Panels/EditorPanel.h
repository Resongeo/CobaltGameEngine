#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	class EditorPanel
	{
	public:
		virtual void Update() = 0;
		virtual void UIRender() = 0;
	};
}