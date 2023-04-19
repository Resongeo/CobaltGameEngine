#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec2 a_Tiling;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in float a_TexIndex;

uniform mat4 ViewProjection;
uniform mat4 Transform;

out vec2 TexCoord;
out vec2 Tiling;
out vec4 Color;
out float TexIndex;

void main()
{
	gl_Position = ViewProjection * vec4(a_Position, 1.0);
	TexCoord = a_TexCoord;
	Tiling = a_Tiling;
	Color = a_Color;
	TexIndex = a_TexIndex;
}

#type fragment
#version 460 core
			
layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec2 Tiling;
in vec4 Color;
in float TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	FragColor = texture(u_Textures[int(TexIndex)], TexCoord * Tiling) * Color;
}
