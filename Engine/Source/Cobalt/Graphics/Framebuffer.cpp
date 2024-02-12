#include "cbpch.h"

#include "Cobalt/Graphics/Framebuffer.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Cobalt
{
	Shared<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLFramebuffer>(specification);
		}
		
		return nullptr;
	}
}