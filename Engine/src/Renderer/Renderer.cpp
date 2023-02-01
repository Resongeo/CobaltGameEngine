#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Cobalt
{
	GraphicsAPI Renderer::s_GraphicsAPI = GraphicsAPI::OpenGL;

	Renderer* Renderer::Create()
	{
		switch (Renderer::s_GraphicsAPI)
		{
			case GraphicsAPI::OpenGL: return new OpenGLRenderer();
		}

		return nullptr;
	}
}