#pragma once

#include "Cobalt/Graphics/VertexBuffer.h"

namespace Cobalt
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(u32 size);
		OpenGLVertexBuffer(float* vertices, u32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		virtual void CopyData(const void* data, u32 size) override;

	private:
		u32 m_RendererID;
		BufferLayout m_Layout;
	};
}