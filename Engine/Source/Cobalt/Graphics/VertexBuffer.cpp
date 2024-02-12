#include "cbpch.h"

#include "Cobalt/Graphics/VertexBuffer.h"

namespace Cobalt
{
	VertexBuffer::VertexBuffer(u32 size)
	{
		glGenBuffers(1, &p_ID);
		glBindBuffer(GL_ARRAY_BUFFER, p_ID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

		LOG_INFO("Created vertex buffer (ID: {}). Size: {}", p_ID, size);
	}

	VertexBuffer::VertexBuffer(float* vertices, u32 size)
	{
		glGenBuffers(1, &p_ID);
		glBindBuffer(GL_ARRAY_BUFFER, p_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		LOG_INFO("Created vertex buffer (ID: {}). Size: {}", p_ID, size);
	}
	
	VertexBuffer::~VertexBuffer()
	{
		LOG_INFO("Deleted vertex buffer (ID: {})", p_ID);

		glDeleteBuffers(1, &p_ID);
	}
	
	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, p_ID);
	}
	
	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}
	
	void VertexBuffer::CopyData(const void* data, u32 size)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}