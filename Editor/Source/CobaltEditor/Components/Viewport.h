#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	class Viewport
	{
	public:
		Viewport(const Vec2& defaultSize);
		Viewport(const Vec2& defaultSize, FramebufferSpecification framebufferSpecs);

		void Begin();
		void End();
		void Draw(uint32_t index);

		void Resize(uint32_t w, uint32_t h);
		int ReadPixel(uint32_t attachmentIndex, int x, int y);

		Ref<Framebuffer> GetFramebuffer() const { return m_Framebuffer; }

		static Ref<Viewport> Create(const Vec2& defaultSize);
		static Ref<Viewport> Create(const Vec2& defaultSize, FramebufferSpecification framebufferSpecs);

	private:
		Ref<Framebuffer> m_Framebuffer;
		Vec2 m_Size;
	};
}