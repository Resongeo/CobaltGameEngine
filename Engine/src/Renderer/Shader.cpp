#include "cbpch.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cobalt
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateRef<OpenGLShader>(filepath);
		}

		return nullptr;
	}
}