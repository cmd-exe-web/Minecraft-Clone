#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_Proj;
uniform mat4 u_View;

out vec2 v_TexCoord;

void main() {
	gl_Position = u_Proj * u_View * position;
	v_TexCoord = texCoord;
}

#shader fragment
#version 460 core

in vec2 v_TexCoord;

uniform sampler2D u_Tex0;

out vec4 FragColor;

void main() {
	// FragColor = vec4(v_TexCoord, 0.0f, 1.0f);
	FragColor = texture2D(u_Tex0, v_TexCoord);
}