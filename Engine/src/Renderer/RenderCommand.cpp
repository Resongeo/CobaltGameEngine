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

	void RenderCommand::DrawIndexed(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model)
	{
		s_Renderer->DrawIndexed(shader, vertexArray, model);
	}

	void RenderCommand::SetViewport(int x, int y, int width, int height)
	{
		s_Renderer->SetViewport(x, y, width, height);
	}
}