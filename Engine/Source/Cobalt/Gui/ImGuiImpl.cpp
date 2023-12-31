#include "cbpch.h"

#include "Cobalt/Gui/ImGuiImpl.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/Gui/OpenGLImGuiImpl.h"

namespace Cobalt
{
	Scope<ImGuiImpl> ImGuiImpl::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateScope<OpenGLImGuiImpl>();
		}

		return nullptr;
	}
}