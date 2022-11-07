#pragma once

#include "Core/Core.h"
#include "Renderer/Shader.h"
#include "Logger/Log.h"

#include "glad/glad.h"

#include <fstream>
#include <string>

namespace Cobalt
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc, ShaderSourceType type);
		~OpenGLShader();

		virtual void Bind() const;

	private:
		unsigned int m_ProgramID;
	};
}