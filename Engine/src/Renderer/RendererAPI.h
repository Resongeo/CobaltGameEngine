#pragma once

#include "Core/Math.h"

#include "Cameras/Camera.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Shader.h"

namespace Cobalt
{
	class RendererAPI
	{
	public:
		virtual void Init() = 0;

		virtual void BeginScene(Camera& camera) = 0;

		virtual void ClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		static RendererAPI* Create();
	};
}