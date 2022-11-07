#pragma once

#include "Renderer/Renderer.h"

#include <string>

namespace Cobalt
{
	enum ShaderSourceType
	{
		String = 0,
		Filepath = 1
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc, ShaderSourceType type);
	};
}