#pragma once

#include "Cobalt/Core/Core.h"

namespace Cobalt
{
	class Texture2D
	{
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetID() const = 0;
		
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot) = 0;

		virtual std::string GetPath() const = 0;

		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);

		virtual bool operator == (const Ref<Texture2D>& other) const = 0;
	};
}