#include "cbpch.h"

#include "Cobalt/Graphics/IndexBuffer.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Cobalt
{
	Ref<IndexBuffer> IndexBuffer::Create(u32* indices, u32 count)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		return nullptr;
	}
}