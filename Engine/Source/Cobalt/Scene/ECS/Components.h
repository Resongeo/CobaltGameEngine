#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Graphics/Texture2D.h"
#include "Cobalt/Graphics/Shader.h"

namespace Cobalt
{
	struct IDComponent
	{
		u64 UUID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
		IDComponent(u64 id) : UUID(id) {}

		operator u64() { return UUID; }
	};

	struct TagComponent
	{
		String Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const String& tag) : Tag(tag) {}

		operator String&() { return Tag; }
		operator const String&() const { return Tag; }
		operator const char*() { return Tag.c_str(); }
	};

	struct TransformComponent
	{
		Vec3 Position = Vec3(0.0f);
		Vec3 Rotation = Vec3(0.0f);
		Vec3 Scale = Vec3(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Vec3& position, const Vec3& rotation, const Vec3& scale)
			: Position(position), Rotation(rotation), Scale(scale) {}

		Mat4 GetTransform() const
		{
			Mat4 rotation = glm::toMat4(glm::quat(glm::radians(Rotation)));

			return glm::translate(Mat4(1.0f), Position)
				* rotation
				* glm::scale(Mat4(1.0f), Scale);
		}
	};

	struct ScriptComponent
	{
		String ClassName;

		ScriptComponent() = default;
		ScriptComponent(const ScriptComponent&) = default;
	};

	struct SpriteRendererComponent
	{
		Shared<Texture2D> Texture = GraphicsObject::Create<Texture2D>(1, 1);
		Color Tint = Color(255);
		Vec2 Tiling = Vec2(1.0f);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Shared<Texture2D>& texture) : Texture(texture) {}

		operator Shared<Texture2D>&() { return Texture; }
		operator const Shared<Texture2D>&() const { return Texture; }
		operator const Color() const { return Tint; }
		operator const Vec4&() const { return Tint; }
		operator const Vec2&() const { return Tiling; }
	};
}