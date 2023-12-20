#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Graphics/Framebuffer.h"

namespace Cobalt
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(u32 width, u32 height) override;
		virtual int ReadPixel(u32 attachmentIndex, int x, int y) override;

		virtual u32 GetColorAttachmentID(int index) const override { if (index <= m_AttachmentIDs.size()) return m_AttachmentIDs[index]; return -1; }
		virtual void ClearAttachment(u32 attachmentIndex, int data) override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; };

	private:
		void Invalidate();
		void Clear();

	private:
		u32 m_RendererID = 0;
		Vector<u32> m_AttachmentIDs;

		FramebufferSpecification m_Specification;
	};
}