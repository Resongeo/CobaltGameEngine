#pragma once

#include "Renderer/IndexBuffer.h"
#include "glad/glad.h"

namespace Cobalt
{
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