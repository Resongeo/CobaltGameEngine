#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Core/Fwd.h"

namespace Cobalt
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Shared<GraphicsContext> Create(GLFWwindow* glfwWindow);
	};
}