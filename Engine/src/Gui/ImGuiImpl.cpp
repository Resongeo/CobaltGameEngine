#include "Gui/ImGuiImpl.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/Gui/OpenGLImGuiImpl.h"

namespace Cobalt
{
	Ref<ImGuiImpl> ImGuiImpl::Create(GLFWwindow* window)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLImGuiImpl>(window);
		}

		return nullptr;
	}
}