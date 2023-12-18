#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"
#include "Cobalt/Rendering/RendererAPI.h"

namespace Cobalt
{
	enum class GraphicsAPI { OpenGL = 0 }; /* For future Vulkan may be supported */

	class Renderer
	{
	public:
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t GetVertexCount() { return QuadCount * 4; }
			uint32_t GetIndexCount() { return QuadCount * 6; }
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