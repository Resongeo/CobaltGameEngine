#pragma once

#include "Core/Core.h"
#include "Core/Math.h"

#include <string>

namespace Cobalt
{
	enum ShaderSourceType
	{
		String = 0,
		Filepath = 1
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;

		virtual inline void SetBool(const char* name, bool value) const = 0;
		virtual inline void SetInt(const char* name, int value) const = 0;
		virtual inline void SetFloat(const char* name, float value) const = 0;
		virtual inline void SetVec2(const char* name, float x, float y) const = 0;
		virtual inline void SetVec2(const char* name, glm::vec2 value) const = 0;
		virtual inline void SetVec3(const char* name, float x, float y, float z) const = 0;
		virtual inline void SetVec3(const char* name, glm::vec3 value) const = 0;
		virtual inline void SetVec4(const char* name, float x, float y, float z, float w) const = 0;
		virtual inline void SetVec4(const char* name, glm::vec4 value) const = 0;
		virtual inline void SetMat4(const char* name, glm::mat4 value) const = 0;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc, ShaderSourceType type);
	};
}