#include "Renderer/IndexBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobalt
{
	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return  CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		return nullptr;
	}
}