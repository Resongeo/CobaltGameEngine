#pragma once

#include "Core/Core.h"

namespace Cobalt
{
	class Texture
	{
	public:
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual uint32_t GetID() = 0;
		
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind() = 0;

		static Ref<Texture> Create(const std::string& path);
		static Ref<Texture> Create(uint32_t width, uint32_t height);
	};
}