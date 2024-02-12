#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Core/Fwd.h"
#include "Cobalt/Graphics/Fwd.h"

namespace Cobalt
{
	class Renderer
	{
	public:
		Renderer() {}

		void Init();
		void BeginScene(const Shared<Camera>& camera);
		void ClearColor(const Color& color);
		void Clear();
		void DrawIndexed(const Shared<VertexArray>& vertexArray, u32 indexCount);
		void SetViewport(int x, int y, int width, int height);

		String GetDefaultShader();

		static Unique<Renderer> Create();

	private:
		Mat4 m_VPM = Mat4(0);
	};
}