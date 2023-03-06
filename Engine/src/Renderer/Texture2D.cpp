#include "cbpch.h"

#include "Renderer/Texture2D.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

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