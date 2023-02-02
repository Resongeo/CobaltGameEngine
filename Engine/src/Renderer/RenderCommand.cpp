#include "Renderer/RenderCommand.h"

namespace Cobalt
{
	Renderer* RenderCommand::s_Renderer = Renderer::Create();

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec2 Tiling;
		glm::vec4 Color;
	};
	
	struct RendererData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TexturedQuadShader;
		Ref<Texture> WhiteTexture;
	};

	static RendererData s_RendererData;

	void RenderCommand::Init()
	{
		s_Renderer->Init();

		uint32_t* quadIndices = new uint32_t[s_RendererData.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_RendererData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		s_RendererData.QuadVertexArray = VertexArray::Create();
		s_RendererData.QuadVertexBuffer = VertexBuffer::Create(s_RendererData.MaxVertices * sizeof(QuadVertex));
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndices, s_RendererData.MaxIndices);

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float2, "a_Tiling" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		s_RendererData.QuadVertexBufferBase = new QuadVertex[s_RendererData.MaxVertices];

		s_RendererData.QuadVertexBuffer->SetLayout(layout);
		s_RendererData.QuadVertexArray->AddVertexBuffer(s_RendererData.QuadVertexBuffer);
		s_RendererData.QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_RendererData.TexturedQuadShader = Shader::Create("assets\\shaders\\TextureShader.glsl");
		s_RendererData.WhiteTexture = Texture::Create("assets\\textures\\white_texture.png");

		delete[] quadIndices;
	}

	void RenderCommand::BeginScene(Camera& camera)
	{
		s_Renderer->BeginScene(camera);

		s_RendererData.TexturedQuadShader->Bind();
		s_RendererData.TexturedQuadShader->SetMat4("ViewProjection", camera.GetViewProjectionMatrix());
		s_RendererData.TexturedQuadShader->SetInt("u_Texture", 0);

		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;
	}

	void RenderCommand::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_RendererData.QuadVertexBufferPtr - (uint8_t*)s_RendererData.QuadVertexBufferBase;
		s_RendererData.QuadVertexBuffer->CopyData(s_RendererData.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void RenderCommand::ClearColor(const glm::vec4& color)
	{
		s_Renderer->ClearColor(color);

	}

	void RenderCommand::Clear()
	{
		s_Renderer->Clear();
	}

	void RenderCommand::Flush()
	{
		s_Renderer->DrawIndexed(s_RendererData.QuadVertexArray, s_RendererData.QuadIndexCount);
	}

	void RenderCommand::DrawQuad(const glm::vec3 position, const glm::vec2 size, const glm::vec4& color)
	{
		DrawQuad(position, size, { 1.0f, 1.0f }, color);
	}

	void RenderCommand::DrawQuad(const glm::vec3 position, const glm::vec2 size, const glm::vec2& tiling, const glm::vec4& color)
	{
		glm::vec2 offset{ size.x * 0.5f, size.y * 0.5f };

		s_RendererData.QuadVertexBufferPtr->Position = { position.x - offset.x, position.y - offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x + offset.x, position.y - offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x + offset.x, position.y + offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x - offset.x, position.y + offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;
	}

	void RenderCommand::SetViewport(int x, int y, int width, int height)
	{
		s_Renderer->SetViewport(x, y, width, height);
	}
}