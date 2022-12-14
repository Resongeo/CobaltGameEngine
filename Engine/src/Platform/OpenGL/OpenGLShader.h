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

		virtual inline void SetBool(const char* name, bool value) const;
		virtual inline void SetInt(const char* name, int value) const;
		virtual inline void SetFloat(const char* name, float value) const;
		virtual inline void SetVec2(const char* name, float x, float y) const;
		virtual inline void SetVec2(const char* name, glm::vec2 value) const;
		virtual inline void SetVec3(const char* name, float x, float y, float z) const;
		virtual inline void SetVec3(const char* name, glm::vec3 value) const;
		virtual inline void SetVec4(const char* name, float x, float y, float z, float w) const;
		virtual inline void SetVec4(const char* name, glm::vec4 value) const;
		virtual inline void SetMat4(const char* name, glm::mat4 value) const;

	private:
		std::string ReadFile(const std::string& filepath);
		Dict<GLenum, std::string> PreProcess(const std::string& source);
		void CompileSources(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;

		mutable Dict<const char*, GLint> m_UniformLocations;
		GLint GetUniformLocation(const char* name) const;
	};
}