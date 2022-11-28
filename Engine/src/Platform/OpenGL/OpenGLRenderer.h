#pragma once

#include "Renderer/Renderer.h"

namespace Cobalt
{
	class OpenGLRenderer : public Renderer
	{
	public:
		virtual void BeginScene(Camera& camera) override;

		virtual void ClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model) override;

		virtual void SetViewport(int x, int y, int width, int height) override;

	private:
		static SceneData* s_SceneData;
	};
}