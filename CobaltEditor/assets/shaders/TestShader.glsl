#type vertex
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
	TexCoord = aTexCoord;
}

#type fragment
#version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec3 vColor;

uniform vec3 inColor;
uniform sampler2D inTexture;

void main()
{
	FragColor = vec4(inColor, 1.0);
}