#include "cbpch.h"

#include "Cobalt/Renderer/Framebuffer.h"

#include "Cobalt/Renderer/Renderer.h"
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