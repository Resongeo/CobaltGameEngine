#pragma once

#include "Cobalt/Graphics/GraphicsObject.h"
#include "Cobalt/Graphics/Fwd.h"

namespace Cobalt
{
	class VertexArray : public GraphicsObject
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer);

		const Vector<Shared<VertexBuffer>>& GetVertexBuffers() const
		{
			return m_VertexBuffers;
		}
		const Shared<IndexBuffer>& GetIndexBuffer() const
		{
			return m_IndexBuffer;
		}

	private:
		Vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer;
	};
}