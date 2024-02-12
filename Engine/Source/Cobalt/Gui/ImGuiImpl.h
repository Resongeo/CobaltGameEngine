#pragma once

#include "Cobalt/Core/Types.h"

namespace Cobalt
{
	class ImGuiImpl
	{
	public:
		ImGuiImpl();

		void NewFrame();
		void Render();
		void ShutDown();

		static Unique<ImGuiImpl> Create();
	};
}