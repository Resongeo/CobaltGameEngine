#type vertex
#version 450 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec2 a_Tiling;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in float a_TexIndex;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec2 v_Tiling;
out vec4 v_Color;
out float v_TexIndex;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
	v_Tiling = a_Tiling;
	v_Color = a_Color;
	v_TexIndex = a_TexIndex;
}

#type fragment
#version 450 core
			
layout(location = 0) out vec4 FragColor;
layout(location = 1) out int EntityID;

in vec2 v_TexCoord;
in vec2 v_Tiling;
in vec4 v_Color;
in float v_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_Tiling) * v_Color;

	if (FragColor.a == 0.0)
		discard;

	EntityID = 10; // Majd megkapja az ECS-bõl
}
