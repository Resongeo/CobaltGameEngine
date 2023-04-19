#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLContext.h"
#include "Cobalt/Renderer/GraphicsContext.h"
#include "Cobalt/Renderer/Renderer.h"

namespace Cobalt
{
	Ref<GraphicsContext> Cobalt::GraphicsContext::Create(GLFWwindow* glfwWindow)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLContext>(glfwWindow);
		}

		return nullptr;
	}
}
