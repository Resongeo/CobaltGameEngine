#pragma once

#include "Cobalt/Logger/Log.h"
#include "Cobalt/Renderer/Framebuffer.h"

namespace Cobalt
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual uint32_t GetColorAttachmentID(uint32_t index) const override { return m_ColorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; };

	private:
		void Invalidate();

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		uint32_t m_EntityAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}