#pragma once

#include "Cobalt/Graphics/VertexArray.h"

namespace Cobalt
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) override;

		virtual const Vector<Shared<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Shared<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		Vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer;

		u32 m_RendererID;
	};
}