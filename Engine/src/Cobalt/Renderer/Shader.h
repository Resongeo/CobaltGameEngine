#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"

#include <string>

namespace Cobalt
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;

		virtual void SetBool(const char* name, bool value) const = 0;
		virtual void SetInt(const char* name, int value) const = 0;
		virtual void SetIntArray(const char* name, int* values, uint32_t count) const = 0;
		virtual void SetFloat(const char* name, float value) const = 0;
		virtual void SetVec2(const char* name, float x, float y) const = 0;
		virtual void SetVec2(const char* name, Vec2 value) const = 0;
		virtual void SetVec3(const char* name, float x, float y, float z) const = 0;
		virtual void SetVec3(const char* name, Vec3 value) const = 0;
		virtual void SetVec4(const char* name, float x, float y, float z, float w) const = 0;
		virtual void SetVec4(const char* name, Vec4 value) const = 0;
		virtual void SetMat4(const char* name, Mat4 value) const = 0;

		static Ref<Shader> Create(const std::string& filepath);
	};
}