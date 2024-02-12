#include "cbpch.h"

#include "Cobalt/Graphics/IndexBuffer.h"

namespace Cobalt
{
	IndexBuffer::IndexBuffer(u32* indices, u32 count) : m_Count(count)
	{
		glGenBuffers(1, &p_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);

		LOG_INFO("Created index buffer (ID: {}). Count: {}", p_ID, count);
	}

	IndexBuffer::~IndexBuffer()
	{
		LOG_INFO("Deleted index buffer (ID: {})", p_ID);

		glDeleteBuffers(1, &p_ID);
	}
	
	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_ID);
	}
	
	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}