#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/Math.h"
#include "Cobalt/Core/Types/String.h"

namespace Cobalt
{
	enum class ShaderSourceType
	{
		Filepath, String
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;

		virtual void SetBool(const char* name, bool value) const = 0;
		virtual void SetInt(const char* name, int value) const = 0;
		virtual void SetIntArray(const char* name, int* values, u32 count) const = 0;
		virtual void SetFloat(const char* name, float value) const = 0;
		virtual void SetVec2(const char* name, float x, float y) const = 0;
		virtual void SetVec2(const char* name, Vec2 value) const = 0;
		virtual void SetVec3(const char* name, float x, float y, float z) const = 0;
		virtual void SetVec3(const char* name, Vec3 value) const = 0;
		virtual void SetVec4(const char* name, float x, float y, float z, float w) const = 0;
		virtual void SetVec4(const char* name, Vec4 value) const = 0;
		virtual void SetMat4(const char* name, Mat4 value) const = 0;

		static Ref<Shader> Create(const String& source, ShaderSourceType sourceType);
	};
}