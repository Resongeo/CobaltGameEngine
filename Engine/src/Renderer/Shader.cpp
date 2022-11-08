#include "Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobalt
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc, ShaderSourceType type)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc, type);
		}

		return nullptr;
	}
}