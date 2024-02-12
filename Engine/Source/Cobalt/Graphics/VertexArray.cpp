#include "cbpch.h"

#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLVertexArray.h"

namespace Cobalt
{
	Shared<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLVertexArray>();
		}

		return nullptr;
	}
}