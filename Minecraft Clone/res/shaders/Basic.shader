#shader vertex
#version 460 core

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec4 v_Color;

uniform vec4 u_Color;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec4 VertexColor;

void main() {
	gl_Position = u_Proj * u_View * (u_Model * v_Position);
	VertexColor = u_Color;
}

#shader fragment
#version 460 core

in vec4 VertexColor;

out vec4 FragColor;

void main() {
	FragColor = VertexColor;
}