#include "cbpch.h"

#include "Renderer/Framebuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

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