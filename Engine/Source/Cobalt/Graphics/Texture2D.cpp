#include "cbpch.h"

#include "Cobalt/Graphics/Texture2D.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLTexture2D.h"

namespace Cobalt
{
	Shared<Texture2D> Texture2D::Create(const String& path)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLTexture>(path);
		}

		return nullptr;
	}

	Shared<Texture2D> Texture2D::Create(u32 width, u32 height)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLTexture>(width, height);
		}

		return nullptr;
	}
}