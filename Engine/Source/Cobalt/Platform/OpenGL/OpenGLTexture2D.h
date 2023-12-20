#pragma once

#include "Cobalt/Graphics/Texture2D.h"

namespace Cobalt
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const String& path);
		OpenGLTexture(u32 width, u32 height);
		virtual ~OpenGLTexture();

		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		virtual u32 GetID() const override { return m_RendererID; };

		virtual String GetPath() const override { return m_Path; };

		virtual void SetData(void* data, u32 size) override;
		virtual void Bind(u32 slot) override;

		virtual bool operator == (const Ref<Texture2D>& other) const override
		{
			return m_RendererID == other->GetID();
		}

	private:
		u32 m_RendererID;
		u32 m_Width, m_Height;
		String m_Path;
	};
}