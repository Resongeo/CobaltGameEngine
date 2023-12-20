#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/String.h"

namespace Cobalt
{
	class Texture2D
	{
	public:
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		virtual u32 GetID() const = 0;
		
		virtual void SetData(void* data, u32 size) = 0;
		virtual void Bind(u32 slot) = 0;

		virtual String GetPath() const = 0;

		static Ref<Texture2D> Create(const String& path);
		static Ref<Texture2D> Create(u32 width, u32 height);

		virtual bool operator == (const Ref<Texture2D>& other) const = 0;
	};
}