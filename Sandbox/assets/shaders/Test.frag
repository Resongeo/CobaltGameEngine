#version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec3 vColor;

uniform vec3 inColor;
uniform sampler2D inTexture;

void main()
{
	//FragColor = texture(inTexture, TexCoord);
	FragColor = vec4(inColor, 1.0);
}