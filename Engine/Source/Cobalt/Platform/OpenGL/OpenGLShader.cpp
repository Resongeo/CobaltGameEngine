#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"
#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	static GLenum ShaderTypeFromString(const String& type)
	{
		if (type == "vertex" || type == "vert" || type == "vt" || type == "v")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "frag" || type == "fg" || type == "f")
			return GL_FRAGMENT_SHADER;

		LOG_ERROR("Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const String& source, ShaderSourceType sourceType)
	{
		std::string src = sourceType == ShaderSourceType::Filepath ? ReadFile(source) : source;
		auto shaderSources = PreProcess(src);
		CompileSources(shaderSources);
	}

	String OpenGLShader::ReadFile(const String& filepath)
	{
		String result;
		std::ifstream stream(filepath, std::ios::in, std::ios::binary);

		if (stream)
		{
			stream.seekg(0, std::ios::end);
			result.resize(stream.tellg());
			stream.seekg(0, std::ios::beg);
			stream.read(&result[0], result.size());
			stream.close();
		}
		else
		{
			LOG_ERROR("Failed to read Shader file: {0}", filepath);
		}

		return result;
	}

	HashMap<GLenum, String> OpenGLShader::PreProcess(const String& source)
	{
		HashMap<GLenum, String> shaderSources;

		const char* typeToken = "#type";
		size typeTokenLength = strlen(typeToken);
		size pos = source.find(typeToken, 0);
		while (pos != String::npos)
		{
			size eol = source.find_first_of("\r\n", pos);
			size begin = pos + typeTokenLength + 1;
			String type = source.substr(begin, eol - begin);

			size nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == String::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::CompileSources(const HashMap<GLenum, String>& shaderSources)
	{
		GLuint program = glCreateProgram();
		Vector<GLenum> glShaderIDs;
		glShaderIDs.reserve(shaderSources.size());
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const String& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				Vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				LOG_ERROR("{0}", infoLog.data());
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		m_RendererID = program;

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			Vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			LOG_ERROR("{0}", infoLog.data());
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}

	/* Uniform setters */

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::SetBool(const char* name, bool value) const
	{
		glUniform1i(GetUniformLocation(name), (int)value);
	}

	void OpenGLShader::SetInt(const char* name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetIntArray(const char* name, int* values, u32 count) const
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void OpenGLShader::SetFloat(const char* name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetVec2(const char* name, float x, float y) const
	{
		glUniform2f(GetUniformLocation(name), x, y);
	}

	void OpenGLShader::SetVec2(const char* name, Vec2 value) const
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetVec3(const char* name, float x, float y, float z) const
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}

	void OpenGLShader::SetVec3(const char* name, Vec3 value) const
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetVec4(const char* name, float x, float y, float z, float w) const
	{
		glUniform4f(GetUniformLocation(name), x, y, z, w);
	}

	void OpenGLShader::SetVec4(const char* name, Vec4 value) const
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const char* name, Mat4 value) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint OpenGLShader::GetUniformLocation(const char* name) const
	{
		if (m_UniformLocations.find(name) != m_UniformLocations.end()) {
			return m_UniformLocations[name];
		}

		GLint location = glGetUniformLocation(m_RendererID, name);
		m_UniformLocations[name] = location;
		return location;
	}
}