#pragma once

#include "Core/Core.h"
#include "Core/Math.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

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
			glm::mat4 rotation =
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), { 1, 0, 0 }) *
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), { 0, 1, 0 }) *
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), { 0, 0, 1 });

			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		Ref<Texture> Sprite = Texture::Create("assets\\textures\\white_texture.png");
		glm::vec4 Color = glm::vec4(1.0);
		glm::vec2 Tiling = glm::vec2(1.0);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : Color(color) {}
		SpriteRendererComponent(const Ref<Texture>& sprite, const glm::vec4& color, const glm::vec2& tiling) : Sprite(sprite), Color(color), Tiling(tiling) {}

		operator Ref<Texture>& () { return Sprite; }
		operator const Ref<Texture>& () const { return Sprite; }

		operator glm::vec4& () { return Color; }
		operator const glm::vec4& () const { return Color; }

		operator glm::vec2& () { return Tiling; }
		operator const glm::vec2& () const { return Tiling; }
	};
}