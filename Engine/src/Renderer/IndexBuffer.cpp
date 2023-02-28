#include "cbpch.h"

#include "Renderer/IndexBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobalt
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return  CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		return nullptr;
	}
}