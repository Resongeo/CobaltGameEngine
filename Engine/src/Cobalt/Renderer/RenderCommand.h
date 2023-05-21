#pragma once

#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Renderer/RendererAPI.h"

namespace Cobalt
{
	class RenderCommand
	{
	public:
		static void BeginScene(const Camera& camera);
		static void EndScene();
		
		static void ClearColor(const Vec4& color);
		static void Clear();

		static void Flush();

		static void DrawQuad(const Vec3& position, const Vec3& scale, const Vec4& color);
		static void DrawQuad(const Vec3& position, const Vec3& rotation, const Vec3& scale, const Vec4& color);
		static void DrawQuad(const Mat4& transform, const Vec2& tiling, const Vec4& color);
		static void DrawQuad(const Mat4& transform, const Vec2& tiling, const Vec4& color, const Ref<Texture2D>& texture);

		static void DrawSprite(const Mat4& transform, const SpriteRendererComponent& spriteComponent);

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