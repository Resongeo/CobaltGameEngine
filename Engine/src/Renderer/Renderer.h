#pragma once

namespace Cobalt
{
	enum class RendererAPI { OpenGL = 0 }; /* For future Vulkan may be supported */

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererApi; }
		inline static RendererAPI SetAPI(RendererAPI rendererAPI)
		{
			s_RendererApi = rendererAPI;
			return s_RendererApi;
		}

		inline static const char* GetAPIString()
		{
			switch (s_RendererApi)
			{
				case Cobalt::RendererAPI::OpenGL: return "OpenGL";
			}

			return "";
		}

	private:
		static RendererAPI s_RendererApi;
	};
}