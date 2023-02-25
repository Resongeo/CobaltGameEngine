#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Cobalt
{
	GraphicsAPI Renderer::s_GraphicsAPI = GraphicsAPI::OpenGL;

	GraphicsAPI Renderer::SetAPI(GraphicsAPI GraphicsAPI)
	{
		s_GraphicsAPI = GraphicsAPI;
		return s_GraphicsAPI;
	}
	
	const char* Renderer::GetAPIString()
	{
		switch (s_GraphicsAPI)
		{
			case Cobalt::GraphicsAPI::OpenGL: return "OpenGL";
		}

		return "";
	}
}