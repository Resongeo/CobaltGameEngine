#include "cbpch.h"

#include "Cobalt/Graphics/Framebuffer.h"

namespace Cobalt
{
	namespace Utils
	{
		enum class AttachmentType
		{
			Color = 0, Integer, Depth
		};

		static bool IsDepthAttachmentType(FramebufferAttachmentType type)
		{
			switch (type)
			{
			case Cobalt::FramebufferAttachmentType::DEPTH24STENCIL8: return true;
			}

			return false;
		}

		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, size count, u32* id)
		{
			glCreateTextures(TextureTarget(multisampled), count, id);
		}

		static void BindTexture(bool multisampled, u32 id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachTexture(int index, u32 id, GLenum internalFormat, GLenum format, const FramebufferSpecification& fbSpec, AttachmentType type)
		{
			bool multisampled = fbSpec.Samples > 1;

			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, fbSpec.Samples, internalFormat, fbSpec.Size.x, fbSpec.Size.y, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, fbSpec.Size.x, fbSpec.Size.y, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			switch (type)
			{
				case Utils::AttachmentType::Color:
				case Utils::AttachmentType::Integer:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
					break;
				case Utils::AttachmentType::Depth:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, TextureTarget(multisampled), id, 0);
					break;
			}
		}
	}

	Framebuffer::Framebuffer(const FramebufferSpecification& specification) : m_Specification(specification)
	{
		m_AttachmentIDs.resize(m_Specification.Attachments.Types.size());
		Invalidate();

		LOG_INFO("Created framebuffer (ID: {}). Attachments: {}", p_ID, m_Specification.Attachments.Types.size());
	}

	Framebuffer::~Framebuffer()
	{
		LOG_INFO("Deleted framebuffer (ID: {})", p_ID);
		Clear();
	}
	
	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, p_ID);
		glViewport(0, 0, m_Specification.Size.x, m_Specification.Size.y);
	}

	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void Framebuffer::Resize(u32 width, u32 height)
	{
		m_Specification.Size.x = width;
		m_Specification.Size.y = height;
		Invalidate();
	}
	
	void Framebuffer::ClearAttachment(u32 attachmentIndex, int data)
	{
		glClearTexImage(m_AttachmentIDs[attachmentIndex], 0, GL_RED_INTEGER, GL_INT, &data);
	}
	
	int Framebuffer::ReadPixel(u32 attachmentIndex, int x, int y)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);

		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);

		return pixelData;
	}
	
	u32 Framebuffer::GetColorAttachmentID(int index) const
	{
		if (index <= m_AttachmentIDs.size())
		{
			return m_AttachmentIDs[index];
		}
		
		return -1;
	}

	void Framebuffer::Invalidate()
	{
		if (p_ID)
		{
			Clear();
		}

		glGenFramebuffers(1, &p_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, p_ID);

		bool multisampled = m_Specification.Samples > 1;

		Utils::CreateTextures(multisampled, m_AttachmentIDs.size(), m_AttachmentIDs.data());

		for (int i = 0; i < m_AttachmentIDs.size(); i++)
		{
			Utils::BindTexture(multisampled, m_AttachmentIDs[i]);

			switch (m_Specification.Attachments.Types[i])
			{
				case FramebufferAttachmentType::RGBA8:
					Utils::AttachTexture(i, m_AttachmentIDs[i], GL_RGBA8, GL_RGBA, m_Specification, Utils::AttachmentType::Color);
					break;
				case FramebufferAttachmentType::RED_INTEGER:
					Utils::AttachTexture(i, m_AttachmentIDs[i], GL_R32I, GL_RED_INTEGER, m_Specification, Utils::AttachmentType::Integer);
					break;
				case FramebufferAttachmentType::DEPTH24STENCIL8:
					Utils::AttachTexture(i, m_AttachmentIDs[i], GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, m_Specification, Utils::AttachmentType::Depth);
					break;
			}
		}

		if (m_AttachmentIDs.size() >= 1)
		{
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_AttachmentIDs.size(), buffers);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR("Framebuffer is not complete!");
		}

		Unbind();
	}
	
	void Framebuffer::Clear()
	{
		glDeleteFramebuffers(1, &p_ID);
		glDeleteTextures(m_AttachmentIDs.size(), m_AttachmentIDs.data());
	}
}