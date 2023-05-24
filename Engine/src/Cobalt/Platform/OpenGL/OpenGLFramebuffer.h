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

		virtual uint32_t GetColorAttachmentID(int index) const override { if (index <= m_AttachmentIDs.size()) return m_AttachmentIDs[index]; }
		virtual void ClearAttachment(uint32_t attachmentIndex, int data) override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; };

	private:
		void Invalidate();
		void Clear();

	private:
		uint32_t m_RendererID = 0;
		std::vector<uint32_t> m_AttachmentIDs;

		FramebufferSpecification m_Specification;
	};
}