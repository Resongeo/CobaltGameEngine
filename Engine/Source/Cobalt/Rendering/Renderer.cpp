#include "cbpch.h"

#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Cameras/Camera.h"
#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Graphics/IndexBuffer.h"

namespace Cobalt
{
	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::BeginScene(const Shared<Camera>& camera)
	{
		m_VPM = camera->GetViewProjectionMatrix();
	}
	
	void Renderer::ClearColor(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Renderer::DrawIndexed(const Shared<VertexArray>& vertexArray, u32 indexCount)
	{
		u32 count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}
	
	String Renderer::GetDefaultShader()
	{
		return String(R"(
			#type vertex
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			layout(location = 2) in vec2 a_Tiling;
			layout(location = 3) in vec4 a_Color;
			layout(location = 4) in float a_TexIndex;
			layout(location = 5) in int a_EntityID;

			uniform mat4 u_ViewProjection;

			out vec2 v_TexCoord;
			out vec2 v_Tiling;
			out vec4 v_Color;
			out float v_TexIndex;
			out flat int v_EntityID;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_TexCoord = a_TexCoord;
				v_Tiling = a_Tiling;
				v_Color = a_Color;
				v_TexIndex = a_TexIndex;
				v_EntityID = a_EntityID;
			}

			#type fragment
			#version 450 core
			
			layout(location = 0) out vec4 FragColor;
			layout(location = 1) out int EntityID;

			in vec2 v_TexCoord;
			in vec2 v_Tiling;
			in vec4 v_Color;
			in float v_TexIndex;
			in flat int v_EntityID;

			uniform sampler2D u_Textures[32];

			void main()
			{
				FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_Tiling) * v_Color;

				if (FragColor.a == 0.0)
					discard;

				EntityID = v_EntityID;
			}
		)");
	}

	Unique<Renderer> Renderer::Create()
	{
		return CreateUnique<Renderer>();
	}
}