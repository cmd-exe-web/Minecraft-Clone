#pragma once

#include <glad/glad.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h" 
#include "IndexBuffer.h"
#include "Shader.h"

#include "Shapes/Cube.h"

class Mesh
{
public:
	Mesh(Cube& cube);
	~Mesh();

	void Render(Shader& shader, glm::vec3 position);
private:
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_IBO;
	Cube& cube;
};
