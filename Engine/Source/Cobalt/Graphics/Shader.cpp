#include "cbpch.h"

#include "Cobalt/Graphics/Shader.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLShader.h"

namespace Cobalt
{
	Shared<Shader> Shader::Create(const String& source, ShaderSourceType sourceType)
	{
		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL: return CreateShared<OpenGLShader>(source, sourceType);
		}

		return nullptr;
	}
}