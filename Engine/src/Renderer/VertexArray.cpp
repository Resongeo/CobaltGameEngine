#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

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