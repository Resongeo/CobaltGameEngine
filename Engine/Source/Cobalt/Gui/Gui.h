#pragma once

#include "Cobalt/Gui/ImGuiImpl.h"

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
		static Unique<ImGuiImpl> s_ImGuiImpl;
	};
}