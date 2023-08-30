#include "cbpch.h"

#include "Cobalt/Graphics/Shader.h"
#include "Cobalt/Rendering/Renderer.h"
#include "Cobalt/Platform/OpenGL/OpenGLShader.h"

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