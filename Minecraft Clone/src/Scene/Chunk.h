#pragma once

#include <vector>

#include "Renderer/Cube.h"
#include "Renderer/Shader.h"

class Chunk {
public:
	Chunk();
	~Chunk();

	void InitChunk();
	void Draw(Shader& shader);
private:
	unsigned int m_Id;
	std::vector<std::vector<std::vector<Cube>>> m_Chunk{ 16, std::vector<std::vector<Cube>> {16, std::vector<Cube> {16}} };
};
