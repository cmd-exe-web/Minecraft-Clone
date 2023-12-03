#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "glm/glm.hpp"

class Cube {
public:
	Cube();
	~Cube();

	void SetPosition(glm::vec3 position);
	void Draw();

	inline glm::mat4 GetModelMatrix() { return model; }
public:
	VertexArray* VAO;
	VertexBuffer* VBO;
	VertexBufferLayout* layout;
	IndexBuffer* IBO;
	glm::mat4 model;
};
