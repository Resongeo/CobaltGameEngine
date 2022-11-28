#pragma once

#include "Renderer/Texture.h"

namespace Cobalt
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& path);

		virtual unsigned int GetWidth() override { return m_Width; }
		virtual unsigned int GetHeight() override { return m_Height; }

		virtual void Bind() override;

	private:
		unsigned int m_RendererID;
		unsigned int m_Width, m_Height;
	};
}