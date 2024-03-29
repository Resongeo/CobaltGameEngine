#include "cbpch.h"

#include "Cobalt/Renderer/RenderCommand.h"

namespace Cobalt
{
	RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();

	struct QuadVertex
	{
		Vec3 Position;
		Vec2 TexCoord;
		Vec2 Tiling;
		Vec4 Color;
		float TexIndex;
		int EntityID;
	};
	
	struct RendererData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureIndexCount = 1;

		Vec4 QuadVertexPositions[4];

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TexturedQuadShader;
		Ref<Texture2D> WhiteTexture;

		Renderer::Statistics Stats;
	};

	static RendererData s_RendererData;

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();

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
			{ ShaderDataType::Float2, "a_Tiling"   },
			{ ShaderDataType::Float4, "a_Color"    },
			{ ShaderDataType::Float,  "a_TexIndex" },
			{ ShaderDataType::Int,    "a_EntityID" }
		};

		s_RendererData.QuadVertexBufferBase = new QuadVertex[s_RendererData.MaxVertices];

		s_RendererData.QuadVertexBuffer->SetLayout(layout);
		s_RendererData.QuadVertexArray->AddVertexBuffer(s_RendererData.QuadVertexBuffer);
		s_RendererData.QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_RendererData.WhiteTexture = Texture2D::Create(1, 1);
		s_RendererData.TexturedQuadShader = Shader::Create(s_RendererAPI->GetDefaultShader(), ShaderSourceType::String);

		int samplers[s_RendererData.MaxTextureSlots];
		for (int i = 0; i < s_RendererData.MaxTextureSlots; i++)
			samplers[i] = i;

		s_RendererData.TexturedQuadShader->Bind();
		s_RendererData.TexturedQuadShader->SetIntArray("u_Textures", samplers, s_RendererData.MaxTextureSlots);

		s_RendererData.TextureSlots[0] = s_RendererData.WhiteTexture;

		s_RendererData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		delete[] quadIndices;
	}

	void RenderCommand::BeginScene(const Camera& camera)
	{
		s_RendererAPI->BeginScene(camera);

		s_RendererData.TexturedQuadShader->Bind();
		s_RendererData.TexturedQuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartBatch();
	}

	void RenderCommand::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_RendererData.QuadVertexBufferPtr - (uint8_t*)s_RendererData.QuadVertexBufferBase;
		s_RendererData.QuadVertexBuffer->CopyData(s_RendererData.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void RenderCommand::ClearColor(const Vec4& color)
	{
		s_RendererAPI->ClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::Flush()
	{
		for (uint32_t i = 0; i < s_RendererData.TextureIndexCount; i++)
		{
			s_RendererData.TextureSlots[i]->Bind(i);
		}

		s_RendererAPI->DrawIndexed(s_RendererData.QuadVertexArray, s_RendererData.QuadIndexCount);

		s_RendererData.Stats.DrawCalls++;
	}

	void RenderCommand::DrawQuad(const Vec3& position, const Vec3& scale, const Color& color)
	{
		if (s_RendererData.QuadIndexCount >= s_RendererData.MaxIndices || s_RendererData.TextureIndexCount >= s_RendererData.MaxTextureSlots)
		{
			EndScene();
			StartBatch();
		}

		Vec2 offset{ scale.x * 0.5f, scale.y * 0.5f };

		float textureIndex = 0.0f;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x - offset.x, position.y - offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x + offset.x, position.y - offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x + offset.x, position.y + offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x - offset.x, position.y + offset.y, position.z };
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.Stats.QuadCount++;
	}

	void RenderCommand::DrawQuad(const Vec3& position, const Vec3& rotation, const Vec3& scale, const Color& color)
	{
		if (s_RendererData.QuadIndexCount >= s_RendererData.MaxIndices || s_RendererData.TextureIndexCount >= s_RendererData.MaxTextureSlots)
		{
			EndScene();
			StartBatch();
		}

		float textureIndex = 0.0f;

		Mat4 transform = glm::translate(Mat4(1.0f), position)
			* glm::rotate(Mat4(1.0f), glm::radians(rotation.x), { 1, 0, 0 })
			* glm::rotate(Mat4(1.0f), glm::radians(rotation.y), { 0, 1, 0 })
			* glm::rotate(Mat4(1.0f), glm::radians(rotation.z), { 0, 0, 1 })
			* glm::scale(Mat4(1.0f), scale);

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = { 1, 1 };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.Stats.QuadCount++;
	}

	void RenderCommand::DrawQuad(const Mat4& transform, const Vec2& tiling, const Color& color, uint32_t entityID)
	{
		if (s_RendererData.QuadIndexCount >= s_RendererData.MaxIndices || s_RendererData.TextureIndexCount >= s_RendererData.MaxTextureSlots)
		{
			EndScene();
			StartBatch();
		}

		uint32_t textureIndex = 0;


		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.Stats.QuadCount++;
	}

	void RenderCommand::DrawQuad(const Mat4& transform, const Vec2& tiling, const Color& color, const Ref<Texture2D>& texture, uint32_t entityID)
	{
		if (s_RendererData.QuadIndexCount >= s_RendererData.MaxIndices || s_RendererData.TextureIndexCount >= s_RendererData.MaxTextureSlots)
		{
			EndScene();
			StartBatch();
		}

		uint32_t textureIndex = 0;
		
		for (uint32_t i = 0; i < s_RendererData.TextureIndexCount; i++)
		{
			if (s_RendererData.TextureSlots[i]->GetID() == texture->GetID())
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0)
		{
			s_RendererData.TextureSlots[s_RendererData.TextureIndexCount] = texture;
			textureIndex = s_RendererData.TextureIndexCount;

			s_RendererData.TextureIndexCount++;
		}


		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->Tiling = tiling;
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RendererData.QuadVertexBufferPtr->EntityID = entityID;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.Stats.QuadCount++;
	}

	void RenderCommand::DrawEntity(const Mat4& transform, const SpriteRendererComponent& spriteComponent, uint32_t entityID)
	{
		DrawQuad(transform, spriteComponent.Tiling, spriteComponent.Tint, spriteComponent.Texture, entityID);
	}

	void RenderCommand::SetViewport(int x, int y, int width, int height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	Renderer::Statistics& RenderCommand::GetStats()
	{
		return s_RendererData.Stats;
	}

	void RenderCommand::ResetStats()
	{
		memset(&s_RendererData.Stats, 0, sizeof(Renderer::Statistics));
	}

	void RenderCommand::StartBatch()
	{
		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;

		s_RendererData.TextureIndexCount = 1;
	}
}