#pragma once

#include "glm/glm.hpp"

#include "Constants.h"
#include "Graphics/Shapes/Cube.h"
#include "Graphics/Shader.h"

class Chunk
{
public:
	Chunk();
	~Chunk();

	void Update();
	bool IsVisible(glm::i32vec3 position);
	bool IsPresent(glm::i32vec3 position);
private:
	bool m_BlockPresent[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
	glm::i32vec3 m_ChunkSize;
};
