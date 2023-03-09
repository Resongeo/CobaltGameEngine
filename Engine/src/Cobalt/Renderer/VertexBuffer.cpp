#include "cbpch.h"

#include "Cobalt/Renderer/VertexBuffer.h"

#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Cobalt
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}

		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		
		return nullptr;
	}
}