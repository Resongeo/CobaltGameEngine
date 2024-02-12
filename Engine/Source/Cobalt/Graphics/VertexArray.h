#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Graphics/VertexBuffer.h"
#include "Cobalt/Graphics/IndexBuffer.h"

namespace Cobalt
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) = 0;

		virtual const Vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

		static Shared<VertexArray> Create();
	};
}