#include "cbpch.h"

#include "Cobalt/Graphics/IndexBuffer.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobalt
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		return nullptr;
	}
}