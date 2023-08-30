#include "cbpch.h"

#include "Cobalt/Graphics/Framebuffer.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Cobalt
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLFramebuffer>(specification);
		}
		
		return nullptr;
	}
}