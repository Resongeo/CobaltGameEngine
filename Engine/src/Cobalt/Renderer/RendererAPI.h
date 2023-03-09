#pragma once

#include "Cobalt/Core/Math.h"

#include "Cobalt/Cameras/Camera.h"

#include "Cobalt/Renderer/VertexArray.h"
#include "Cobalt/Renderer/Texture2D.h"
#include "Cobalt/Renderer/Shader.h"

namespace Cobalt
{
	class RendererAPI
	{
	public:
		virtual void Init() = 0;

		virtual void BeginScene(const Camera& camera) = 0;

		virtual void ClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		static RendererAPI* Create();
	};
}