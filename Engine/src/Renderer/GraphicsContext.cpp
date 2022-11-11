#include "Renderer/GraphicsContext.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Cobalt
{
	Ref<GraphicsContext> Cobalt::GraphicsContext::Create(GLFWwindow* glfwWindow)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLContext>(glfwWindow);
		}
	}
}
