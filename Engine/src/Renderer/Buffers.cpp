#include "Buffers.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffers.h"

namespace Cobalt
{
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}
}