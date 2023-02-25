#pragma once

#include "Gui/ImGuiImpl.h"

namespace Cobalt
{
	class Gui
	{
	public:
		static void Init();
		static void NewFrame();
		static void Render();
		static void ShutDown();

	private:
		static Scope<ImGuiImpl> s_ImGuiImpl;
	};
}