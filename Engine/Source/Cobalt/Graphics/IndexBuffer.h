#pragma once

#include "Cobalt/Core/Core.h"

namespace Cobalt
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual u32 GetCount() const = 0;

		static Ref<IndexBuffer> Create(u32* indices, u32 count);
	};
}