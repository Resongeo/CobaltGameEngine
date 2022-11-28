#pragma once

#include "Renderer/Texture.h"

namespace Cobalt
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& path);

		virtual uint32_t GetWidth() override { return m_Width; }
		virtual uint32_t GetHeight() override { return m_Height; }

		virtual void Bind() override;

	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
	};
}