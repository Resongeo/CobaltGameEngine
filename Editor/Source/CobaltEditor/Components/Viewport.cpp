#include "pch.h"
#include "CobaltEditor/Components/Viewport.h"

namespace CobaltEditor
{
	Viewport::Viewport(const Vec2& defaultSize) : m_Size(defaultSize)
	{
		FramebufferSpecification framebufferSpecs;
		framebufferSpecs.Attachments = { FramebufferAttachmentType::RGBA8 };
		framebufferSpecs.Size = m_Size;
		framebufferSpecs.Samples = 1;
		m_Framebuffer = Framebuffer::Create(framebufferSpecs);
	}

	Viewport::Viewport(const Vec2& defaultSize, FramebufferSpecification framebufferSpecs) : m_Size(defaultSize)
	{
		framebufferSpecs.Size = m_Size;
		m_Framebuffer = Framebuffer::Create(framebufferSpecs);
	}

	void Viewport::Begin()
	{
		m_Framebuffer->Bind();
	}

	void Viewport::End()
	{
		m_Framebuffer->Unbind();
	}

	void Viewport::Draw(uint32_t index)
	{
		ImGui::Image((ImTextureID)m_Framebuffer->GetColorAttachmentID(index), { m_Size.x, m_Size.y }, ImVec2{0, 1}, ImVec2{1, 0});
	}

	void Viewport::Resize(uint32_t w, uint32_t h)
	{
		m_Size = Vec2(w, h);
		m_Framebuffer->Resize(w, h);
	}

	int Viewport::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		return m_Framebuffer->ReadPixel(attachmentIndex, x, y);
	}

	Ref<Viewport> Viewport::Create(const Vec2& defaultSize)
	{
		return CreateRef<Viewport>(defaultSize);
	}
	Ref<Viewport> Viewport::Create(const Vec2& defaultSize, FramebufferSpecification framebufferSpecs)
	{
		return CreateRef<Viewport>(defaultSize, framebufferSpecs);
	}
}