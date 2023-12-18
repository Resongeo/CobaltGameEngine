#pragma once

#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Rendering/RendererAPI.h"

namespace Cobalt
{
	class OpenGLRenderer : public Renderer, public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void BeginScene(const Ref<Camera>& camera) override;

		virtual void ClearColor(const Color& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

		virtual void SetViewport(int x, int y, int width, int height) override;

		virtual std::string GetDefaultShader() override;

	private:
		static SceneData* s_SceneData;
	};
}