#pragma once

#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"

namespace Cobalt
{
	class OpenGLRenderer : public Renderer, public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void BeginScene(Camera& camera) override;

		virtual void ClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

		virtual void SetViewport(int x, int y, int width, int height) override;

	private:
		static SceneData* s_SceneData;
	};
}