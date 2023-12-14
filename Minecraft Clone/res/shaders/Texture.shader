#shader vertex
#version 460 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Proj;
uniform mat4 u_View;

out vec2 v_TexCoord;

void main() {
	gl_Position = u_Proj * u_View * a_Position;
	v_TexCoord = a_TexCoord;
}

#shader fragment
#version 460 core

in vec2 v_TexCoord;

uniform sampler2D u_Tex0;

out vec4 FragColor;

void main() {
	FragColor = texture2D(u_Tex0, v_TexCoord);
}