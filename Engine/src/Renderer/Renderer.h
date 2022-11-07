#pragma once

namespace Cobalt
{
	enum class RendererAPI { OpenGL = 0 }; /* For future Vulkan may be supported */

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererApi; }
		inline static RendererAPI SetAPI(RendererAPI rendererAPI) { s_RendererApi = rendererAPI; }

	private:
		static RendererAPI s_RendererApi;
	};
}