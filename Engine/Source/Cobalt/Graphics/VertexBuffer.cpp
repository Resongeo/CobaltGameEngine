#include "cbpch.h"

#include "Cobalt/Graphics/VertexBuffer.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Cobalt
{
	Ref<VertexBuffer> VertexBuffer::Create(u32 size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}

		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, u32 size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		
		return nullptr;
	}
}