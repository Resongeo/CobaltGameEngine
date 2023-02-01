#pragma once

#include "Renderer/Renderer.h"

namespace Cobalt
{
	class RenderCommand
	{
	public:
		static void Init();
		static void BeginScene(Camera& camera);
		
		static void ClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, const glm::vec2& tiling, const Ref<Texture>& texture);

		static void SetViewport(int x, int y, int width, int height);

	private:
		static Renderer* s_Renderer;
	};
}