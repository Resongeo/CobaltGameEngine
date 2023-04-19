#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLRenderer.h"
#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Renderer/RenderCommand.h"

namespace Cobalt
{
	GraphicsAPI Renderer::s_GraphicsAPI = GraphicsAPI::OpenGL;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

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