#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Rendering/RendererAPI.h"
#include "Cobalt/Scene/ECS/Components.h"

namespace Cobalt
{
	class RenderCommand
	{
	public:
		static void BeginScene(const Shared<Camera>& camera);
		static void EndScene();
		
		static void ClearColor(const Color& color);
		static void Clear();

		static void Flush();

		static void DrawQuad(const Vec3& position, const Vec3& scale, const Color& color);
		static void DrawQuad(const Vec3& position, const Vec3& rotation, const Vec3& scale, const Color& color);
		static void DrawQuad(const Mat4& transform, const Vec2& tiling, const Color& color, u32 entityID);
		static void DrawQuad(const Mat4& transform, const Vec2& tiling, const Color& color, const Shared<Texture2D>& texture, u32 entityID);

		static void DrawEntity(const Mat4& transform, const SpriteRendererComponent& spriteComponent, u32 entityID);

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