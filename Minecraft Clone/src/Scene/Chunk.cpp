#include "Chunk.h"

#include "Graphics/Renderer/CubeRenderer.h"
#include "Scene/TerrainGenerator.h"

glm::i32vec3 neighbours[6] = {
	{  0,  0,  1 },
	{  0,  0, -1 },
	{ -1,  0,  0 },
	{  1,  0,  0 },
	{  0,  1,  0 },
	{  0, -1,  0 },
};

Chunk::Chunk()
	:m_ChunkSize({CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z})
{
	memset(m_BlockPresent, 0, sizeof(m_BlockPresent));

	for (int i = 0; i < m_ChunkSize.x; i++) {
		for (int j = 0; j < m_ChunkSize.y; j++) {
			for (int k = 0; k < m_ChunkSize.z; k++) {
				// m_BlockPresent[i][j][k] = true;
				m_BlockName[i][j][k] = BlockName::Dirt;

				// if (j > 127) {
					// m_BlockPresent[i][j][k] = false;
				// }
			}
		}
	}

	TerrainGenerator::GenerateRandomTerrain(m_BlockPresent);

	m_BlockName[0][0][0] = BlockName::Cobblestone;
	m_BlockName[0][0][1] = BlockName::Cobblestone;
	m_BlockName[0][0][2] = BlockName::Cobblestone;
	m_BlockName[0][0][3] = BlockName::Cobblestone;
	m_BlockName[0][1][3] = BlockName::Cobblestone;
	m_BlockPresent[0][0][m_ChunkSize.z / 2] = false;
	m_BlockPresent[0][4][m_ChunkSize.z / 2] = false;
	m_BlockPresent[1][4][m_ChunkSize.z / 2] = false;
	m_BlockPresent[1][5][m_ChunkSize.z / 2] = false;
}

Chunk::~Chunk()
{
}

void Chunk::Render()
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
				CubeRenderer::DrawCube(cubeBuilder, {i, j, k});
			}
		}
	}
}

bool Chunk::IsVisible(glm::i32vec3 position)
{
	for (const auto& neighbour : neighbours) {
		if (!IsPresent(position + neighbour))
			return true;
	}
	return false;
}

bool Chunk::IsPresent(glm::i32vec3 position)
{
	if (position.x < 0 || position.y < 0 || position.z < 0 || position.x == m_ChunkSize.x || position.y == m_ChunkSize.y || position.z == m_ChunkSize.z)
		return false;
	return m_BlockPresent[position.x][position.y][position.z];
}
