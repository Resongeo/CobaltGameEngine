#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Graphics/IndexBuffer.h"

namespace Cobalt
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(u32* indices, u32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual u32 GetCount() const { return m_Count; }

	private:
		u32 m_RendererID;
		u32 m_Count;
	};
}