#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Cobalt
{
	static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
	{
		switch (type)
		{
			case Cobalt::ShaderDataType::Int:	 return GL_INT;
			case Cobalt::ShaderDataType::Int2:	 return GL_INT;
			case Cobalt::ShaderDataType::Int3:   return GL_INT;
			case Cobalt::ShaderDataType::Int4:   return GL_INT;
			case Cobalt::ShaderDataType::Float:  return GL_FLOAT;
			case Cobalt::ShaderDataType::Float2: return GL_FLOAT;
			case Cobalt::ShaderDataType::Float3: return GL_FLOAT;
			case Cobalt::ShaderDataType::Float4: return GL_FLOAT;
			case Cobalt::ShaderDataType::Mat3:   return GL_FLOAT;
			case Cobalt::ShaderDataType::Mat4:   return GL_FLOAT;
		}
		return GL_FALSE;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetElementCount(),
				ShaderDataTypeToGLenum(element.Type),
				GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}