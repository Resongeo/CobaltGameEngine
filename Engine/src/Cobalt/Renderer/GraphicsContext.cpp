#include "cbpch.h"

#include "Cobalt/Renderer/GraphicsContext.h"

#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLContext.h"

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
