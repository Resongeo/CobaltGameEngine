#include "cbpch.h"

#include "Cobalt/Graphics/Texture2D.h"
#include <stb_image.h>

namespace Cobalt
{
	Texture2D::Texture2D(const String& path) : m_Path(path)
	{
		if (!std::filesystem::exists(path))
		{
			LOG_ERROR("Failed to load texture: {0}", path);
			Texture2D _(1, 1);
		}

		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = channels == 4 ? GL_RGBA8 : GL_RGB8;
		GLenum dataFormat = channels == 4 ? GL_RGBA : GL_RGB;

		glCreateTextures(GL_TEXTURE_2D, 1, &p_ID);
		glTextureStorage2D(p_ID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(p_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(p_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(p_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(p_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(p_ID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		LOG_INFO("Created texture (ID: {}). Path: {}", p_ID, m_Path);
	}

	Texture2D::Texture2D(u32 width, u32 height) : m_Width(width), m_Height(height), m_Path("Default Texture")
	{
		Vector<unsigned char> tempBuffer;
		tempBuffer.resize(m_Width * m_Height * 4, 255);

		glCreateTextures(GL_TEXTURE_2D, 1, &p_ID);
		glTextureStorage2D(p_ID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(p_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(p_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(p_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(p_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(p_ID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, tempBuffer.data());

		LOG_INFO("Created texture (ID: {}). Size: {}x{}", p_ID, m_Width, m_Height);
	}
	
	Texture2D::~Texture2D()
	{
		LOG_INFO("Deleted texture (ID: {})", p_ID);

		glDeleteTextures(1, &p_ID);
	}
	
	void Texture2D::Bind(u32 slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, p_ID);
	}
	
	void Texture2D::SetData(void* data, u32 size)
	{
		glTexSubImage2D(p_ID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}