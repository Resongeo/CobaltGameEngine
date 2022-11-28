#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobalt
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc, ShaderSourceType type)
	{
		m_ProgramID = 0;

		const char* vertShaderCode;
		const char* fragShaderCode;

		if (type == ShaderSourceType::Filepath)
		{
			std::string vertCode;
			std::string fragCode;
			std::ifstream vertShaderFile;
			std::ifstream fragShaderFile;

			vertShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
			fragShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);

			try
			{
				vertShaderFile.open(vertexSrc);
				fragShaderFile.open(fragmentSrc);
				std::stringstream vertShaderStream, fragShaderStream;

				vertShaderStream << vertShaderFile.rdbuf();
				fragShaderStream << fragShaderFile.rdbuf();

				vertShaderFile.close();
				fragShaderFile.close();

				vertCode = vertShaderStream.str();
				fragCode = fragShaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				LOG_ENGINE_ERROR("Failed to open shader files: {0} {1}!", vertexSrc, fragmentSrc);
			}

			vertShaderCode = vertCode.c_str();
			fragShaderCode = fragCode.c_str();
			LOG_ENGINE_FATAL(vertCode.c_str());
			LOG_ENGINE_FATAL(fragCode.c_str());
		}
		else
		{
			vertShaderCode = vertexSrc.c_str();
			fragShaderCode = fragmentSrc.c_str();
		}

		uint32_t vertex, fragment;
		int succes;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			LOG_ENGINE_ERROR("Failed to compile vertex shader: {0}", infoLog);
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			LOG_ENGINE_ERROR("Failed to compile fragment shader: {0}", infoLog);
		}

		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, vertex);
		glAttachShader(m_ProgramID, fragment);
		glLinkProgram(m_ProgramID);

		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			glGetProgramInfoLog(m_ProgramID, 512, NULL, infoLog);
			LOG_ENGINE_ERROR("Failed to create shader program!");
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		LOG_ENGINE_INFO("Shader loaded!");
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ProgramID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::SetBool(const char* name, bool value) const
	{
		glUniform1i(GetUniformLocation(name), (int)value);
	}

	void OpenGLShader::SetInt(const char* name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat(const char* name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetVec2(const char* name, float x, float y) const
	{
		glUniform2f(GetUniformLocation(name), x, y);
	}

	void OpenGLShader::SetVec2(const char* name, glm::vec2 value) const
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetVec3(const char* name, float x, float y, float z) const
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}

	void OpenGLShader::SetVec3(const char* name, glm::vec3 value) const
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetVec4(const char* name, float x, float y, float z, float w) const
	{
		glUniform4f(GetUniformLocation(name), x, y, z, w);
	}

	void OpenGLShader::SetVec4(const char* name, glm::vec4 value) const
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.y, value.w);
	}

	void OpenGLShader::SetMat4(const char* name, glm::mat4 value) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint OpenGLShader::GetUniformLocation(const char* name) const
	{
		if (m_UniformLocations.find(name) != m_UniformLocations.end()) {
			return m_UniformLocations[name];
		}

		GLint location = glGetUniformLocation(m_ProgramID, name);
		m_UniformLocations[name] = location;
		return location;
	}
}