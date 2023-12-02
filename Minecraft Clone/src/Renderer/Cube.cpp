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
	4--|- - - - - - -5	|              \  
	 \ |			  \	|               \
	  \|			   \|                Z
	   0- - - - - - - --1
*/
	GLfloat vertices[] = {
	//      Position           	    TexCoord
		// Front 
		-0.5f, -0.5f,  0.5f,       0.0f, 0.0f,       // 0
		 0.5f, -0.5f,  0.5f,       1.0f, 0.0f,       // 1
		 0.5f,  0.5f,  0.5f,       1.0f, 1.0f,       // 2
		-0.5f,  0.5f,  0.5f,       0.0f, 1.0f,       // 3 

		// Back
		-0.5f, -0.5f, -0.5f,       1.0f, 0.0f,       // 4
		 0.5f, -0.5f, -0.5f,       0.0f, 0.0f,       // 5
		 0.5f,  0.5f, -0.5f,       0.0f, 1.0f,       // 6
		-0.5f,  0.5f, -0.5f,       1.0f, 1.0f,       // 7

		// Left
		-0.5f, -0.5f, -0.5f,       0.0f, 0.0f,       // 4   ->  8
		-0.5f, -0.5f,  0.5f,       1.0f, 0.0f,       // 0   ->  9
		-0.5f,  0.5f,  0.5f,       1.0f, 1.0f,       // 3   ->  10
		-0.5f,  0.5f, -0.5f,       0.0f, 1.0f,       // 7   ->  11

		// Right
		 0.5f, -0.5f,  0.5f,       0.0f, 0.0f,       // 1   ->  12
		 0.5f, -0.5f, -0.5f,       1.0f, 0.0f,       // 5   ->  13
		 0.5f,  0.5f, -0.5f,       1.0f, 1.0f,       // 6   ->  14
		 0.5f,  0.5f,  0.5f,       0.0f, 1.0f,       // 2   ->  15

		 // Top
		-0.5f,  0.5f,  0.5f,       0.0f, 0.0f,       // 3   ->  16
		 0.5f,  0.5f,  0.5f,       1.0f, 0.0f,       // 2   ->  17
		 0.5f,  0.5f, -0.5f,       1.0f, 1.0f,       // 6   ->  18
		-0.5f,  0.5f, -0.5f,       0.0f, 1.0f,       // 7   ->  19

		// Bottom
		-0.5f, -0.5f,  0.5f,       1.0f, 0.0f,       // 0   ->  20
		-0.5f, -0.5f, -0.5f,       1.0f, 1.0f,       // 4   ->  21
		 0.5f, -0.5f, -0.5f,       0.0f, 1.0f,       // 5   ->  22
		 0.5f, -0.5f,  0.5f,       0.0f, 0.0f,       // 1   ->  23
	};
	GLuint indices[] = {
		 0,  1,  2,
		 2,  3,  0,   // Front

		 6,  5,  4,
		 4,  7,  6,   // Back

		 8,  9, 10,
		10, 11,  8,   // Left

		12, 13, 14,
		14, 15, 12,   // right

		16, 17, 18,
		18, 19, 16,   // Top

		20, 21, 22,
		22, 23, 20,   // Base
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
