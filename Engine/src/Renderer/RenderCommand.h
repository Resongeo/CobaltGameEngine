#pragma once

#include "Renderer/Renderer.h"

namespace Cobalt
{
	class RenderCommand
	{
	public:
		static void BeginScene(Camera& camera);
		static void ClearColor(const glm::vec4& color);
		static void Clear();
		static void DrawIndexed(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model);

	private:
		static Renderer* s_Renderer;
	};
}