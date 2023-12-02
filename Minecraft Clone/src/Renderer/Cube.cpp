#include "Cube.h"

#include <glad/glad.h>

Cube::Cube()
	:VAO(nullptr), VBO(nullptr), layout(nullptr)
{
	GLfloat vertices[] = {
	//      Position                        Color
		-0.5f, -0.5f,  0.5f,         1.0f, 0.5f, 1.0f, 1.0f,    // 0         Bottom left front
		 0.5f, -0.5f,  0.5f,         0.0f, 1.0f, 0.0f, 1.0f,    // 1         Bottom right front
		 0.5f, -0.5f, -0.5f,         0.0f, 0.0f, 1.0f, 1.0f,    // 2         Bottom right back
		-0.5f, -0.5f, -0.5f,         0.2f, 0.5f, 0.3f, 1.0f,    // 3         Bottom left back

		-0.5f,  0.5f,  0.5f,         1.0f, 0.0f, 0.0f, 1.0f,    // 4            Top left front
		 0.5f,  0.5f,  0.5f,         0.0f, 1.0f, 0.0f, 1.0f,    // 5            Top right front
		 0.5f,  0.5f, -0.5f,         0.0f, 0.0f, 1.0f, 1.0f,    // 6            Top right back
		-0.5f,  0.5f, -0.5f,         0.2f, 0.6f, 0.8f, 1.0f,    // 7            Top left back

	};
	
	VAO = new VertexArray;
	VBO = new VertexBuffer(vertices, sizeof(vertices));
	layout = new VertexBufferLayout;
	layout->Push<float>(3);
	layout->Push<float>(4);

	VAO->AddBuffers(*VBO, *layout);
	VAO->Unbind();

	GLuint indices[] = {
		0, 2, 1, 
		0, 3, 2,  // Base

		0, 1, 5,
		0, 5, 4,  // Front

		4, 5, 6,
		4, 6, 7,  // Top

		2, 3, 7,
		2, 7, 6, // Back

		3, 0, 4,
		3, 4, 7, // Left

		1, 2, 6,
		1, 6, 5  // right
	};
	IBO = new IndexBuffer(indices, sizeof(indices));
	IBO->Unbind();
}

Cube::~Cube()
{
}

void Cube::Update()
{
}

void Cube::Draw()
{
	VAO->Bind();
	IBO->Bind();
	glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_INT, 0);
}
