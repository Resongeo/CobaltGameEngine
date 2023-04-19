#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLRenderer.h"
#include "Cobalt/Renderer/RendererAPI.h"
#include "Cobalt/Renderer/Renderer.h"

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