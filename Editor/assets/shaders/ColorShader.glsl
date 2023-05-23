#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 ViewProjection;
uniform mat4 Transform;

out vec2 TexCoord;

void main()
{
	gl_Position = ViewProjection * Transform * vec4(a_Position, 1.0);
	TexCoord = a_TexCoord;
}

#type fragment
#version 450 core

layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 u_Color;

void main()
{
	FragColor = u_Color;
}