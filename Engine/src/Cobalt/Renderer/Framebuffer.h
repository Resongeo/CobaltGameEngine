#pragma once

#include "Cobalt/Core/Core.h"

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
		std::vector<FramebufferAttachmentType> Types;

		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferAttachmentType> types) : Types(types) {}
	};

	struct FramebufferSpecification
	{
		FramebufferAttachmentSpecification Attachments;
		uint32_t Width, Height = 1;
		uint32_t Samples = 1;
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual uint32_t GetColorAttachmentID(int index) const = 0;
		virtual void ClearAttachment(uint32_t attachmentIndex, int data) = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specification);
	};
}