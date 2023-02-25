#pragma once

#include "Core/Core.h"
#include "Renderer/Shader.h"
#include "Logger/Log.h"

#include <fstream>
#include <string>

#include <glad/glad.h>

namespace Cobalt
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() const;

		virtual void SetBool(const char* name, bool value) const override;
		virtual void SetInt(const char* name, int value) const override;
		virtual void SetIntArray(const char* name, int* values, uint32_t count) const override;
		virtual void SetFloat(const char* name, float value) const override;
		virtual void SetVec2(const char* name, float x, float y) const override;
		virtual void SetVec2(const char* name, glm::vec2 value) const override;
		virtual void SetVec3(const char* name, float x, float y, float z) const override;
		virtual void SetVec3(const char* name, glm::vec3 value) const override;
		virtual void SetVec4(const char* name, float x, float y, float z, float w) const override;
		virtual void SetVec4(const char* name, glm::vec4 value) const override;
		virtual void SetMat4(const char* name, glm::mat4 value) const override;

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