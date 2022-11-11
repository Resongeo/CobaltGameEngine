#pragma once

#include "Core/Core.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Cobalt
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Ref<GraphicsContext> Create(GLFWwindow* glfwWindow);
	};
}