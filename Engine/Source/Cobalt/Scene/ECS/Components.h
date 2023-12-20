#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/Math.h"
#include "Cobalt/Core/Types/Color.h"
#include "Cobalt/Core/Types/String.h"
#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Graphics/Texture2D.h"
#include "Cobalt/Graphics/Shader.h"
#include "Cobalt/Scene/ECS/LuaEntity.h"

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

	struct SpriteRendererComponent
	{
		Ref<Texture2D> Texture = Texture2D::Create(1, 1);
		Color Tint = Color(255);
		Vec2 Tiling = Vec2(1.0f);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Ref<Texture2D>& texture) : Texture(texture) {}

		operator Ref<Texture2D>&() { return Texture; }
		operator const Ref<Texture2D>&() const { return Texture; }
		operator const Color() const { return Tint; }
		operator const Vec4&() const { return Tint; }
		operator const Vec2&() const { return Tiling; }
	};

	enum class LuaScriptSourceType
	{
		None = 0, Filepath, String
	};

	struct LuaScriptComponent
	{
		LuaEntity ScriptEntity;
		sol::state LuaState;
		String Source;
		LuaScriptSourceType SourceType = LuaScriptSourceType::None;
		bool HasScriptLoaded = false;

		LuaScriptComponent() = default;
		LuaScriptComponent(const LuaScriptComponent&) = default;
		LuaScriptComponent(const String& source, LuaScriptSourceType sourceType) : Source(source), SourceType(sourceType) {}
	};
}