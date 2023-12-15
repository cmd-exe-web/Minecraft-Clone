#include "Chunk.h"

#include "Graphics/Renderer/CubeRenderer.h"
#include "World/TerrainGenerator.h"

const int CHUNK_LENGTH = 16;

glm::i32vec3 neighbours[6] = {
	{  0,  0,  1 },
	{  0,  0, -1 },
	{ -1,  0,  0 },
	{  1,  0,  0 },
	{  0,  1,  0 },
	{  0, -1,  0 },
};

Chunk::Chunk(glm::i32vec3 chunkPosition)
	:m_ChunkPosition(chunkPosition), m_ChunkSize({ CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z })
{
	TerrainGenerator::GenerateFlatTerrain(m_BlockName);
}

Chunk::~Chunk()
{
}

void Chunk::Render() const
{
	for (int i = 0; i < m_ChunkSize.x; i++) {
		for (int j = 0; j < m_ChunkSize.y; j++) {
			for (int k = 0; k < m_ChunkSize.z; k++) {
				if (!IsPresent({i, j, k}) || !IsVisible({i, j, k})) {
					continue;
				}
				CubeBuilder cubeBuilder;
				glm::i32vec3 current(i, j, k);
				if (!IsPresent(current + neighbours[(int)Direction::Front]))
					cubeBuilder.AddFaces(Direction::Front);
				if (!IsPresent(current + neighbours[(int)Direction::Back]))
					cubeBuilder.AddFaces(Direction::Back);
				if (!IsPresent(current + neighbours[(int)Direction::Left]))
					cubeBuilder.AddFaces(Direction::Left);
				if (!IsPresent(current + neighbours[(int)Direction::Right]))
					cubeBuilder.AddFaces(Direction::Right);
				if (!IsPresent(current + neighbours[(int)Direction::Top]))
					cubeBuilder.AddFaces(Direction::Top);
				if (!IsPresent(current + neighbours[(int)Direction::Bottom]))
					cubeBuilder.AddFaces(Direction::Bottom);
				cubeBuilder.AddBlockType(m_BlockName[i][j][k]);
				CubeRenderer::DrawCube(cubeBuilder, { i + m_ChunkPosition.x * CHUNK_LENGTH, j, k + m_ChunkPosition.z * CHUNK_LENGTH });
			}
		}
	}
}

bool Chunk::IsVisible(glm::i32vec3 position) const
{
	for (const auto& neighbour : neighbours) {
		if (!IsPresent(position + neighbour))
			return true;
	}
	return false;
}

bool Chunk::IsPresent(glm::i32vec3 position) const
{
	if (position.x < 0 || position.y < 0 || position.z < 0 || position.x == m_ChunkSize.x || position.y == m_ChunkSize.y || position.z == m_ChunkSize.z)
		return false;

	return (m_BlockName[position.x][position.y][position.z] != BlockName::None);
}
