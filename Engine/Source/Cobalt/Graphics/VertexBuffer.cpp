#include "cbpch.h"

#include "Cobalt/Graphics/VertexBuffer.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Cobalt
{
	Shared<VertexBuffer> VertexBuffer::Create(u32 size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLVertexBuffer>(size);
		}

		return nullptr;
	}

	Shared<VertexBuffer> VertexBuffer::Create(float* vertices, u32 size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLVertexBuffer>(vertices, size);
		}
		
		return nullptr;
	}
}