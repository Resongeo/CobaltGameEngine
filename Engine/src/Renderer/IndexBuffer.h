#pragma once

#include "Core/Core.h"

namespace Cobalt
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int count);
	};
}