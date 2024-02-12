#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Cameras/Camera.h"
#include "Cobalt/Graphics/VertexArray.h"

namespace Cobalt
{
	class RendererAPI
	{
	public:
		virtual void Init() = 0;

		virtual void BeginScene(const Shared<Camera>& camera) = 0;

		virtual void ClearColor(const Color& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Shared<VertexArray>& vertexArray, u32 indexCount = 0) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		virtual String GetDefaultShader() = 0;

		static RendererAPI* Create();
	};
}