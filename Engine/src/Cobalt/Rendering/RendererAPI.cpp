#include "cbpch.h"

#include "Cobalt/Rendering/RendererAPI.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLRenderer.h"

namespace Cobalt
{
	RendererAPI* RendererAPI::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return new OpenGLRenderer();
		}

		return nullptr;
	}
}