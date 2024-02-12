#pragma once

#include "Cobalt/Core/Types.h"

namespace Cobalt
{
	class GraphicsObject
	{
	public:
		virtual void Bind() const {}
		virtual void Unbind() const {}

		template<typename T, typename ... Args>
		static Shared<T> Create(Args&& ... args)
		{
			return CreateShared<T>(std::forward<Args>(args)...);
		}

	protected:
		RenderID p_ID = 0;
	};
}