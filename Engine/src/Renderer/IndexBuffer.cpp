#include "Renderer/IndexBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobalt
{
	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}
}