#pragma once

#include "Cobalt/Core/Types.h"

namespace Cobalt
{
	class ImGuiImpl
	{
	public:
		virtual void NewFrame() = 0;
		virtual void Render() = 0;
		virtual void ShutDown() = 0;

		static Unique<ImGuiImpl> Create();
	};
}