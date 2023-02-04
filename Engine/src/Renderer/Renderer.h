#pragma once

#include "Core/Core.h"
#include "Core/Math.h"

#include "Cameras/Camera.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

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

		static Renderer* Create();

	public:
		virtual void Init() = 0;

		virtual void BeginScene(Camera& camera) = 0;

		virtual void ClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

	private:
		static GraphicsAPI s_GraphicsAPI;

	protected:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
	};
}