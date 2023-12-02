#include "Cube.h"

#include <glad/glad.h>

Cube::Cube()
	:VAO(nullptr), VBO(nullptr), layout(nullptr)
{
/*
	7- - - - - - - --6
	|\               |\
	| \				 | \
	|  3- - - - - - - - 2             Y
	|  |			 |	|             |
	|  |			 |	|             | 
	|  |	   .	 |	|             |_ _ _ _ X
	4- |- - - - - - -5	|            /
	 \ |			  \	|           /
	  \|			   \|          Z
	   0- - - - - - - --1
*/
	GLfloat vertices[] = {
	//      Position           	    TexCoord
		-0.5f, -0.5f,  0.5f,       0.0f, 0.0f,       // 0
		 0.5f, -0.5f,  0.5f,       1.0f, 0.0f,       // 1
		 0.5f,  0.5f,  0.5f,       1.0f, 1.0f,       // 2
		-0.5f,  0.5f,  0.5f,       0.0f, 1.0f,       // 3

		-0.5f, -0.5f, -0.5f,       0.0f, 0.0f,       // 4
		 0.5f, -0.5f, -0.5f,       1.0f, 0.0f,       // 5
		 0.5f,  0.5f, -0.5f,       1.0f, 1.0f,       // 6
		-0.5f,  0.5f, -0.5f,       0.0f, 1.0f,       // 7
	};
	GLuint indices[] = {
		0, 1, 2, 
		2, 3, 0,  // Front

		6, 5, 4,
		4, 7, 6, // Back

		0, 4, 5,
		5, 1, 0,  // Base

		3, 2, 6,
		6, 7, 3,  // Top

		4, 0, 3,
		3, 7, 4, // Left

		1, 5, 6,
		6, 2, 1  // right
	};
	
	VAO = new VertexArray;
	VBO = new VertexBuffer(vertices, sizeof(vertices));
	layout = new VertexBufferLayout;
	layout->Push<float>(3);
	layout->Push<float>(2);

	VAO->AddBuffers(*VBO, *layout);
	VAO->Unbind();

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
