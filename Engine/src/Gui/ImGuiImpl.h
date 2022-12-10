#pragma once

#include "Core/Core.h"

#include <imgui.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cobalt
{
	class ImGuiImpl
	{
	public:
		virtual void NewFrame() = 0;
		virtual void Render() = 0;
		virtual void ShutDown() = 0;

		static Ref<ImGuiImpl> Create(GLFWwindow* window);
	};
}