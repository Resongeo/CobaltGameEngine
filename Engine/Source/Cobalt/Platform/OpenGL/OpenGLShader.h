#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/String.h"
#include "Cobalt/Core/Types/DataStructures.h"	
#include "Cobalt/Graphics/Shader.h"

#include <fstream>
#include <glad/glad.h>

namespace Cobalt
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const String& source, ShaderSourceType sourceType);
		virtual ~OpenGLShader();

		virtual void Bind() const;

		virtual void SetBool(const char* name, bool value) const override;
		virtual void SetInt(const char* name, int value) const override;
		virtual void SetIntArray(const char* name, int* values, u32 count) const override;
		virtual void SetFloat(const char* name, float value) const override;
		virtual void SetVec2(const char* name, float x, float y) const override;
		virtual void SetVec2(const char* name, Vec2 value) const override;
		virtual void SetVec3(const char* name, float x, float y, float z) const override;
		virtual void SetVec3(const char* name, Vec3 value) const override;
		virtual void SetVec4(const char* name, float x, float y, float z, float w) const override;
		virtual void SetVec4(const char* name, Vec4 value) const override;
		virtual void SetMat4(const char* name, Mat4 value) const override;

	private:
		String ReadFile(const String& filepath);
		HashMap<GLenum, String> PreProcess(const String& source);
		void CompileSources(const HashMap<GLenum, String>& shaderSources);

	private:
		u32 m_RendererID;
		mutable HashMap<const char*, GLint> m_UniformLocations;
		GLint GetUniformLocation(const char* name) const;
	};
}