#include "cbpch.h"

#include "Cobalt/Graphics/GraphicsContext.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLContext.h"

namespace Cobalt
{
	Shared<GraphicsContext> Cobalt::GraphicsContext::Create(GLFWwindow* glfwWindow)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLContext>(glfwWindow);
		}

		return nullptr;
	}
}
