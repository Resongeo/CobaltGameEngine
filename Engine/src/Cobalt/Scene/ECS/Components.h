#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"

#include "Cobalt/Renderer/VertexArray.h"
#include "Cobalt/Renderer/Texture2D.h"
#include "Cobalt/Renderer/Shader.h"

namespace Cobalt
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) {}

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
		operator const char* () { return Tag.c_str(); }
	};

	struct TransformComponent
	{
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
			: Position(position), Rotation(rotation), Scale(scale) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Position)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		Ref<Texture2D> Texture;
		glm::vec4 Color = glm::vec4(1.0);
		glm::vec2 Tiling = glm::vec2(1.0);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Ref<Texture2D>& sprite) : Texture(sprite) {}

		operator Ref<Texture2D>& () { return Texture; }
		operator const Ref<Texture2D>& () const { return Texture; }

		operator glm::vec4& () { return Color; }
		operator const glm::vec4& () const { return Color; }

		operator glm::vec2& () { return Tiling; }
		operator const glm::vec2& () const { return Tiling; }
	};
}