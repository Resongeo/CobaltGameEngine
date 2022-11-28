#include "Renderer/Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Cobalt
{
	Ref<Texture> Texture::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLTexture>(path);
		}
	}
}