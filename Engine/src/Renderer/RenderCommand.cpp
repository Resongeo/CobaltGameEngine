#include "Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Cobalt
{
	Renderer* RenderCommand::s_Renderer = new OpenGLRenderer;

	void RenderCommand::BeginScene(Camera& camera)
	{
		s_Renderer->BeginScene(camera);
	}

	void RenderCommand::ClearColor(const glm::vec4& color)
	{
		s_Renderer->ClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_Renderer->Clear();
	}

	void RenderCommand::DrawIndexed(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		s_Renderer->DrawIndexed(shader, vertexArray);
	}
}