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
	};

	struct TransformComponent
	{
		glm::mat4 Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		Ref<Texture> Sprite;
		glm::vec4 Color;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Ref<Texture>& sprite, const glm::vec4& color): Sprite(sprite), Color(color) {}

		operator Ref<Texture>& () { return Sprite; }
		operator const Ref<Texture>& () const { return Sprite; }

		operator glm::vec4& () { return Color; }
		operator const glm::vec4& () const { return Color; }
	};
}