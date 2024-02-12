#pragma once

#include "Cobalt/Core/Types.h"

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

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(u32 width, u32 height) = 0;
		virtual int ReadPixel(u32 attachmentIndex, int x, int y) = 0;

		virtual u32 GetColorAttachmentID(int index) const = 0;
		virtual void ClearAttachment(u32 attachmentIndex, int data) = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Shared<Framebuffer> Create(const FramebufferSpecification& specification);
	};
}