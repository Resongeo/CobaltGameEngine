#pragma once

#include "Renderer/Renderer.h"

namespace Cobalt
{
	class OpenGLRenderer : public Renderer
	{
	public:
		virtual void ClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}