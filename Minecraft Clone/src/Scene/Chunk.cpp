#include "Chunk.h"

#include "glm/glm.hpp"

Chunk::Chunk()
	:m_Id(1)
{
}

Chunk::~Chunk()
{
}

void Chunk::InitChunk()
{
	int x = 0;
	int y = 0;
	int z = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
				m_Chunk[i][j].SetPosition(glm::vec3(i, 0, j));
		}
	}
}

void Chunk::Draw(Shader& shader)
{
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			shader.SetUniformMat4("u_Model", m_Chunk[i][j].GetModelMatrix());
			m_Chunk[i][j].Draw();
		}
	}

}
