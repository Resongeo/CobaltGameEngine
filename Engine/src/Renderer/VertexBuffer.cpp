#include "Renderer/VertexBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Cobalt
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		return nullptr;
	}
}