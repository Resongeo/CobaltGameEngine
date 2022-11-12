#include "Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Cobalt
{
	Renderer* RenderCommand::s_Renderer = new OpenGLRenderer;

	void RenderCommand::ClearColor(const glm::vec4& color)
	{
		s_Renderer->ClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_Renderer->Clear();
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_Renderer->DrawIndexed(vertexArray);
	}
}