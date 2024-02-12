#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Rendering/RendererAPI.h"

namespace Cobalt
{
	class OpenGLRenderer : public Renderer, public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void BeginScene(const Shared<Camera>& camera) override;

		virtual void ClearColor(const Color& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Shared<VertexArray>& vertexArray, u32 indexCount = 0) override;

		virtual void SetViewport(int x, int y, int width, int height) override;

		virtual String GetDefaultShader() override;

	private:
		static SceneData* s_SceneData;
	};
}