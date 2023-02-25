#pragma once

#include "Core/Core.h"

#include <imgui.h>

struct GLFWwindow;

namespace Cobalt
{
	class ImGuiImpl
	{
	public:
		virtual void NewFrame() = 0;
		virtual void Render() = 0;
		virtual void ShutDown() = 0;

		static Scope<ImGuiImpl> Create(GLFWwindow* window);
	};
}