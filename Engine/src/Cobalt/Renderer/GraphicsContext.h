#pragma once

#include "Cobalt/Core/Core.h"

struct GLFWwindow;

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