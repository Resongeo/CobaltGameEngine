#pragma once

#include "Core/Core.h"
#include "Core/Math.h"

#include "Renderer/VertexArray.h"

namespace Cobalt
{
	enum class GraphicsAPI { OpenGL = 0 }; /* For future Vulkan may be supported */

	class Renderer
	{
	public:
		inline static GraphicsAPI GetAPI() { return s_GraphicsAPI; }
		inline static GraphicsAPI SetAPI(GraphicsAPI GraphicsAPI)
		{
			s_GraphicsAPI = GraphicsAPI;
			return s_GraphicsAPI;
		}

		inline static const char* GetAPIString()
		{
			switch (s_GraphicsAPI)
			{
				case Cobalt::GraphicsAPI::OpenGL: return "OpenGL";
			}

			return "";
		}

	public:
		virtual void ClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

	private:
		static GraphicsAPI s_GraphicsAPI;
	};
}