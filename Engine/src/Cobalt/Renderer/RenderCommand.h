#pragma once

#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Renderer/RendererAPI.h"
#include "Cobalt/Scene/ECS/Components.h"

namespace Cobalt
{
	class RenderCommand
	{
	public:
		static void BeginScene(const Camera& camera);
		static void EndScene();
		
		static void ClearColor(const glm::vec4& color);
		static void Clear();

		static void Flush();

		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec2& tiling, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec2& tiling, const glm::vec4& color, const Ref<Texture2D>& texture);

		static void DrawSprite(const glm::mat4& transform, const SpriteRendererComponent& spriteComponent);

		static void SetViewport(int x, int y, int width, int height);

		static Renderer::Statistics& GetStats();
		static void ResetStats();

	private:
		static void Init();
		static void StartBatch();

		friend class Renderer;

	private:
		static RendererAPI* s_RendererAPI;
	};
}