#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/Math.h"
#include "Cobalt/Rendering/RendererAPI.h"
#include "Cobalt/Graphics/GraphicsAPI.h"

namespace Cobalt
{
	class Renderer
	{
	public:
		struct Statistics
		{
			u32 DrawCalls = 0;
			u32 QuadCount = 0;
			u32 GetVertexCount() const { return QuadCount * 4; }
			u32 GetIndexCount() const { return QuadCount * 6; }
		};

		static GraphicsAPI GetAPI() { return s_GraphicsAPI; }
		static GraphicsAPI SetAPI(GraphicsAPI GraphicsAPI);

		static const char* GetAPIString();

	private:
		static void Init();
		friend class Application;

	private:
		static GraphicsAPI s_GraphicsAPI;

	protected:
		struct SceneData
		{
			Mat4 ViewProjectionMatrix;
		};
	};
}