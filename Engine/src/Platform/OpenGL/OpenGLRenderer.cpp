#include "Platform/OpenGL/OpenGLRenderer.h"

#include "glad/glad.h"

namespace Cobalt
{
	Renderer::SceneData* OpenGLRenderer::s_SceneData = new Renderer::SceneData();

	void OpenGLRenderer::BeginScene(Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void OpenGLRenderer::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::DrawIndexed(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		shader->SetMat4("View", s_SceneData->ViewProjectionMatrix);
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}