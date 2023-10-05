#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLFramebuffer.h"
#include "Cobalt/Logger/Log.h"

#include <glad/glad.h>

namespace Cobalt
{
	namespace FBUtils
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

		static void CreateTextures(bool multisampled, size_t count, uint32_t* id)
		{
			glCreateTextures(TextureTarget(multisampled), count, id);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachTexture(int index, uint32_t id, GLenum internalFormat, GLenum format, const FramebufferSpecification& fbSpec, AttachmentType type)
		{
			bool multisampled = fbSpec.Samples > 1;

			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, fbSpec.Samples, internalFormat, fbSpec.Width, fbSpec.Height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, fbSpec.Width, fbSpec.Height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			switch (type)
			{
				case Cobalt::FBUtils::AttachmentType::Color:
				case Cobalt::FBUtils::AttachmentType::Integer:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
					break;
				case Cobalt::FBUtils::AttachmentType::Depth:
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, TextureTarget(multisampled), id, 0);
					break;
			}
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification) : m_Specification(specification)
	{
		m_AttachmentIDs.resize(m_Specification.Attachments.Types.size());
		Invalidate();
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			Clear();
		}

		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisampled = m_Specification.Samples > 1;

		FBUtils::CreateTextures(multisampled, m_AttachmentIDs.size(), m_AttachmentIDs.data());

		for (int i = 0; i < m_AttachmentIDs.size(); i++)
		{
			FBUtils::BindTexture(multisampled, m_AttachmentIDs[i]);

			switch (m_Specification.Attachments.Types[i])
			{
				case FramebufferAttachmentType::RGBA8:
					FBUtils::AttachTexture(i, m_AttachmentIDs[i], GL_RGBA8, GL_RGBA, m_Specification, FBUtils::AttachmentType::Color);
					break;										  
				case FramebufferAttachmentType::RED_INTEGER:	  
					FBUtils::AttachTexture(i, m_AttachmentIDs[i], GL_R32I, GL_RED_INTEGER, m_Specification, FBUtils::AttachmentType::Integer);
					break;										  
				case FramebufferAttachmentType::DEPTH24STENCIL8:  
					FBUtils::AttachTexture(i, m_AttachmentIDs[i], GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, m_Specification, FBUtils::AttachmentType::Depth);
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

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		Clear();
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;
		Invalidate();
	}

	void OpenGLFramebuffer::Clear()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_AttachmentIDs.size(), m_AttachmentIDs.data());
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t index, int x, int y)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);

		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);

		return pixelData;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int data)
	{
		glClearTexImage(m_AttachmentIDs[attachmentIndex], 0, GL_RED_INTEGER, GL_INT, &data);
	}
}