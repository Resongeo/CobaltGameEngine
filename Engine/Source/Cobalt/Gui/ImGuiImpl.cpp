#include "cbpch.h"

#include "Cobalt/Gui/ImGuiImpl.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/Gui/OpenGLImGuiImpl.h"

namespace Cobalt
{
	Unique<ImGuiImpl> ImGuiImpl::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateUnique<OpenGLImGuiImpl>();
		}

		return nullptr;
	}
}