#pragma once

#include "Cobalt/Renderer/GraphicsContext.h"
#include "Cobalt/Logger/Log.h"

struct GFLWwindow;

namespace Cobalt
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* glfwWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}