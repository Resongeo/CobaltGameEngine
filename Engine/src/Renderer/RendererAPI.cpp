#include "Renderer/RendererAPI.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLRenderer.h"

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