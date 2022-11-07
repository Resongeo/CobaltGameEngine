#include "OpenGLShader.h"

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
		}
		else
		{
			vertShaderCode = vertexSrc.c_str();
			fragShaderCode = fragmentSrc.c_str();
		}

		unsigned int vertex, fragment;
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
}