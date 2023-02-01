#pragma once

#include "Renderer/Texture.h"

namespace Cobalt
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& path);
		OpenGLTexture(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture();

		virtual uint32_t GetWidth() override { return m_Width; }
		virtual uint32_t GetHeight() override { return m_Height; }
		virtual uint32_t GetID() const override { return m_RendererID; };

		virtual std::string GetPath() const override  { return m_Path; };

		virtual void SetData(void* data, uint32_t size) override;
		virtual void Bind() override;

	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;

		std::string m_Path;
	};
}