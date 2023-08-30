#include "cbpch.h"

#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLVertexArray.h"

namespace Cobalt
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		return nullptr;
	}
}