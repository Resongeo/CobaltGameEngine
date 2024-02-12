#pragma once

#include "Cobalt/Graphics/GraphicsObject.h"

namespace Cobalt
{
	enum class ShaderSourceType
	{
		Filepath, String
	};

	class Shader : public GraphicsObject
	{
	public:
		Shader(const String& source, ShaderSourceType sourceType);
		~Shader();

		void Bind() const override;
		void Unbind() const override;

		void SetBool(const char* name, bool value) const;
		void SetInt(const char* name, int value) const;
		void SetIntArray(const char* name, int* values, u32 count) const;
		void SetFloat(const char* name, float value) const;
		void SetVec2(const char* name, float x, float y) const;
		void SetVec2(const char* name, const Vec2& value) const;
		void SetVec3(const char* name, float x, float y, float z) const;
		void SetVec3(const char* name, const Vec3& value) const;
		void SetVec4(const char* name, float x, float y, float z, float w) const;
		void SetVec4(const char* name, const Vec4& value) const;
		void SetMat4(const char* name, const Mat4& value) const;

	private:
		String ReadFile(const String& filepath);
		HashMap<u32, String> PreProcess(const String& source);

		void CompileSources(const HashMap<u32, String>& shaderSources);

	private:
		i32 GetUniformLocation(const char* name) const;
		mutable HashMap<const char*, i32> m_UniformLocations;
	};
}