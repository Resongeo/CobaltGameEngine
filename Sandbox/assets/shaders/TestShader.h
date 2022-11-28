#pragma once

#include <string>

/* Temporary solution for removing the shader source from main.cpp.Loading from a file does not work currently. */

namespace TestShader
{
	std::string Vertex = R"(
		#version 460 core
			
		layout(location = 0) in vec3 aPosition;
		layout(location = 1) in vec3 aColor;
		layout(location = 2) in vec2 aTexCoord;

		uniform mat4 View;
		uniform mat4 Model;

		out vec3 vColor;
		out vec2 TexCoord;

		void main()
		{
			gl_Position = View * Model * vec4(aPosition, 1.0);
			vColor = aColor;
		}
	)";

	std::string Fragment = R"(
		#version 460 core
			
		layout(location = 0) out vec4 FragColor;

		in vec3 vColor;

		uniform vec3 inColor;

		void main()
		{
			FragColor = vec4(inColor, 1.0);
		}
	)";
}