#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class Cube {
public:
	Cube();
	~Cube();

	void Update();
	void Draw();
public:
	VertexArray* VAO;
	VertexBuffer* VBO;
	VertexBufferLayout* layout;
	IndexBuffer* IBO;
};
