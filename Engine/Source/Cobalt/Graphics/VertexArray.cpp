#include "cbpch.h"

#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Graphics/VertexBuffer.h"
#include "Cobalt/Graphics/IndexBuffer.h"

namespace Cobalt
{
	namespace Utils
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
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &p_ID);
		glBindVertexArray(p_ID);

		LOG_INFO("Created vertex array (ID: {})", p_ID);
	}
	
	VertexArray::~VertexArray()
	{
		LOG_INFO("Deleted vertex array (ID: {})", p_ID);

		glDeleteBuffers(1, &p_ID);
	}
	
	void VertexArray::Bind() const
	{
		glBindVertexArray(p_ID);
	}
	
	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void VertexArray::AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer)
	{
		Bind();
		vertexBuffer->Bind();

		u32 index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
				glEnableVertexAttribArray(index);
				glVertexAttribIPointer(
					index,
					element.GetElementCount(),
					Utils::ShaderDataTypeToGLenum(element.Type),
					layout.GetStride(),
					(const void*)element.Offset
				);
				break;
			default:
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index,
					element.GetElementCount(),
					Utils::ShaderDataTypeToGLenum(element.Type),
					GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset
				);
				break;
			}

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}