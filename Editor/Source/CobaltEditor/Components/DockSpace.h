#pragma once

#include "Cobalt.h"

namespace CobaltEditor
{
	class DockSpace
	{
	public:
		static void MasterSpace(const Shared<Cobalt::Window>& window);

	private:
		static float s_ToolbarHeight;
	};
}