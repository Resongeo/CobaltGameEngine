#include "Renderer/RenderCommand.h"

namespace Cobalt
{
	Renderer* RenderCommand::s_Renderer = Renderer::Create();

	struct RendererData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TexturedQuadShader;
		Ref<Texture> WhiteTexture;
	};

	static RendererData s_RendererData;

	void RenderCommand::Init()
	{
		float vertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};

		s_Renderer->Init();

		s_RendererData.QuadVertexArray = VertexArray::Create();
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};

		vertexBuffer->SetLayout(layout);
		s_RendererData.QuadVertexArray->AddVertexBuffer(vertexBuffer);
		s_RendererData.QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_RendererData.TexturedQuadShader = Shader::Create("assets\\shaders\\TextureShader.glsl");
		s_RendererData.WhiteTexture = Texture::Create("assets\\textures\\white_texture.png");
	}

	void RenderCommand::BeginScene(Camera& camera)
	{
		s_Renderer->BeginScene(camera);

		s_RendererData.TexturedQuadShader->Bind();
		s_RendererData.TexturedQuadShader->SetInt("u_Texture", 0);
	}

	void RenderCommand::ClearColor(const glm::vec4& color)
	{
		s_Renderer->ClearColor(color);

	}

	void RenderCommand::Clear()
	{
		s_Renderer->Clear();
	}

	void RenderCommand::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		s_RendererData.TexturedQuadShader->SetVec4("u_Color", color);
		s_RendererData.WhiteTexture->Bind();
		s_Renderer->DrawIndexed(s_RendererData.TexturedQuadShader, s_RendererData.QuadVertexArray, transform);
	}

	void RenderCommand::DrawQuad(const glm::mat4& transform, const glm::vec4& color, const glm::vec2& tiling, const Ref<Texture>& texture)
	{
		s_RendererData.TexturedQuadShader->SetVec4("u_Color", color);
		s_RendererData.TexturedQuadShader->SetVec2("u_Tiling", tiling);
		texture->Bind();
		s_Renderer->DrawIndexed(s_RendererData.TexturedQuadShader, s_RendererData.QuadVertexArray, transform);
	}

	void RenderCommand::SetViewport(int x, int y, int width, int height)
	{
		s_Renderer->SetViewport(x, y, width, height);
	}
}