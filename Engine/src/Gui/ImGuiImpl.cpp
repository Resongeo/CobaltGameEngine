#include "Gui/ImGuiImpl.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/Gui/OpenGLImGuiImpl.h"

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