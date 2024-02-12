#pragma once

#include "Cobalt/Graphics/GraphicsObject.h"

namespace Cobalt
{
	class IndexBuffer : public GraphicsObject
	{
	public:
		IndexBuffer(u32* indices, u32 count);
		~IndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		u32 GetCount() const
		{
			return m_Count;
		}

	private:
		u32 m_Count = 0;
	};
}