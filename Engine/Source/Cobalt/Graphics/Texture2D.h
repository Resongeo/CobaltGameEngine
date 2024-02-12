#pragma once

#include "Cobalt/Graphics/GraphicsObject.h"

namespace Cobalt
{
	class Texture2D : public GraphicsObject
	{
	public:
		Texture2D(const String& path);
		Texture2D(u32 width, u32 height);
		~Texture2D();

		u32 GetWidth() const { return m_Width; }
		u32 GetHeight() const { return m_Height; }
		String GetPath() const { return m_Path; }
		RenderID GetID() const { return p_ID; }
		
		void Bind(u32 slot);
		void SetData(void* data, u32 size);

		bool operator == (const Shared<Texture2D>& other) const
		{
			return p_ID == other->GetID();
		}

	private:
		u32 m_Width = 0;
		u32 m_Height = 0;
		String m_Path;
	};
}