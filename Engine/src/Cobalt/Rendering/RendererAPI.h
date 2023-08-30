#pragma once

#include "Cobalt/Cameras/Camera.h"
#include "Cobalt/Core/Math.h"
#include "Cobalt/Graphics/VertexArray.h"

namespace Cobalt
{
	class RendererAPI
	{
	public:
		virtual void Init() = 0;

		virtual void BeginScene(const Camera& camera) = 0;

		virtual void ClearColor(const Vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		virtual std::string GetDefaultShader() = 0;

		static RendererAPI* Create();
	};
}