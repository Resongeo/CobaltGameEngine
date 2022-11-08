#include "GraphicsContext.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Cobalt
{
	GraphicsContext* Cobalt::GraphicsContext::Create(GLFWwindow* glfwWindow)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLContext(glfwWindow);
		}
	}
}
