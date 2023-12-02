#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 u_Proj;
uniform mat4 u_View;

out vec4 v_Color;

void main() {
	gl_Position = u_Proj * u_View * position;
	v_Color = color;
}

#shader fragment
#version 460 core

in vec4 v_Color;

out vec4 FragColor;

void main() {
	FragColor = v_Color;
}