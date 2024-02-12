#pragma once

#include "Cobalt/Graphics/GraphicsObject.h"

namespace Cobalt
{
	enum class FramebufferAttachmentType
	{
		None = 0,
		RGBA8,
		RED_INTEGER,
		DEPTH24STENCIL8
	};

	struct FramebufferAttachmentSpecification
	{
		Vector<FramebufferAttachmentType> Types;

		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(InitializerList<FramebufferAttachmentType> types) : Types(types) {}
	};

	struct FramebufferSpecification
	{
		FramebufferAttachmentSpecification Attachments;
		Vec2 Size = Vec2(1);
		u32 Samples = 1;
	};

	class Framebuffer : public GraphicsObject
	{
	public:
		Framebuffer(const FramebufferSpecification& specification);
		~Framebuffer();

		void Bind() const override;
		void Unbind() const override;

		void Resize(u32 width, u32 height);
		void ClearAttachment(u32 attachmentIndex, int data);

		int ReadPixel(u32 attachmentIndex, int x, int y);
		u32 GetColorAttachmentID(int index) const;

		const FramebufferSpecification& GetSpecification() const
		{
			return m_Specification;
		}

	private:
		void Invalidate();
		void Clear();

	private:
		FramebufferSpecification m_Specification;
		Vector<u32> m_AttachmentIDs;
	};
}