#pragma once

#include "Core/Core.h"

namespace Cobalt
{
	class Texture
	{
	public:
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual void Bind() = 0;

		static Ref<Texture> Create(const std::string& path);
	};
}