#include "cbpch.h"

#include "Cobalt/Gui/ImGuiImpl.h"
#include "Cobalt/Platform/OpenGL/Gui/OpenGLImGuiImpl.h"
#include "Cobalt/Renderer/Renderer.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cobalt
{
	Scope<ImGuiImpl> ImGuiImpl::Create(GLFWwindow* window)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateScope<OpenGLImGuiImpl>(window);
		}

		return nullptr;
	}
}