#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLShader.h"
#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Renderer/Shader.h"

namespace Cobalt
{
	Ref<Shader> Shader::Create(const std::string& source, ShaderSourceType sourceType)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLShader>(source, sourceType);
		}

		return nullptr;
	}
}