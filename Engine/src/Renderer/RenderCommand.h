#pragma once

#include "Renderer/Renderer.h"

namespace Cobalt
{
	class RenderCommand
	{
	public:
		static void ClearColor(const glm::vec4& color);
		static void Clear();
		static void DrawIndexed(const Ref<VertexArray>& vertexArray);

	private:
		static Renderer* s_Renderer;
	};
}