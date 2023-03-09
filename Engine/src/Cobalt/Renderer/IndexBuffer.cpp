#include "cbpch.h"

#include "Cobalt/Renderer/IndexBuffer.h"

#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLIndexBuffer.h"

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