#pragma once

#include "Renderer/Buffers.h"
#include "glad/glad.h"

namespace Cobalt
{/*
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
	}*/

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }	

	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual unsigned int GetCount() const { return m_Count; }

	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}