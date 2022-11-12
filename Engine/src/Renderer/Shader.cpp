#include "Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobalt
{
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc, ShaderSourceType type)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc, type);
		}

		return nullptr;
	}
}