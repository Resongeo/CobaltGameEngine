#include "cbpch.h"

#include "Cobalt/Graphics/Texture2D.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLTexture2D.h"

namespace Cobalt
{
	Ref<Texture2D> Texture2D::Create(const String& path)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLTexture>(path);
		}

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(u32 width, u32 height)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLTexture>(width, height);
		}

		return nullptr;
	}
}