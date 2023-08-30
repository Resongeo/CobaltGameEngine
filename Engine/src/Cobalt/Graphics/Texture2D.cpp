#include "cbpch.h"

#include "Cobalt/Graphics/Texture2D.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLTexture2D.h"

namespace Cobalt
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLTexture>(path);
		}

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLTexture>(width, height);
		}

		return nullptr;
	}
}