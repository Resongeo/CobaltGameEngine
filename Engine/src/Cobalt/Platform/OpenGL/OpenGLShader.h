#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Renderer/Shader.h"
#include "Cobalt/Logger/Log.h"

#include <fstream>
#include <string>

#include <glad/glad.h>

namespace Cobalt
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& source, ShaderSourceType sourceType);
		virtual ~OpenGLShader();

		virtual void Bind() const;

		virtual void SetBool(const char* name, bool value) const override;
		virtual void SetInt(const char* name, int value) const override;
		virtual void SetIntArray(const char* name, int* values, uint32_t count) const override;
		virtual void SetFloat(const char* name, float value) const override;
		virtual void SetVec2(const char* name, float x, float y) const override;
		virtual void SetVec2(const char* name, Vec2 value) const override;
		virtual void SetVec3(const char* name, float x, float y, float z) const override;
		virtual void SetVec3(const char* name, Vec3 value) const override;
		virtual void SetVec4(const char* name, float x, float y, float z, float w) const override;
		virtual void SetVec4(const char* name, Vec4 value) const override;
		virtual void SetMat4(const char* name, Mat4 value) const override;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void CompileSources(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		mutable std::unordered_map<const char*, GLint> m_UniformLocations;
		GLint GetUniformLocation(const char* name) const;
	};
}