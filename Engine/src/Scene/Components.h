#pragma once

#include "Core/Core.h"
#include "Core/Math.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

namespace Cobalt
{
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
	};
}