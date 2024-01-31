#include "Chunk.h"

#include <utility>

#include "Graphics/Renderer/CubeRenderer.h"
#include "World/TerrainGenerator.h"
#include "ChunkManager.h"

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

void Chunk::Render(ChunkManager& chunkManager) const
{
	for (int i = 0; i < m_ChunkSize.x; i++) {
		for (int j = 0; j < m_ChunkSize.y; j++) {
			for (int k = 0; k < m_ChunkSize.z; k++) {
				if (!IsPresent({i, j, k}) || !IsVisible({i, j, k})) {
					continue;
				}
				auto [atOuterSurface, adjacentChunkPosition] = IsOuterBlock({i, j, k});
				if (atOuterSurface && chunkManager.IsChunkLoaded(adjacentChunkPosition.x, adjacentChunkPosition.z)) {
					if (!IsPresent({ i, j + 1, k })) {
						CubeBuilder cubeBuilder;
						cubeBuilder.AddFace(Direction::Top);
						cubeBuilder.AddBlockType(BlockName::Dirt);
						CubeRenderer::DrawCube(cubeBuilder, { i + m_ChunkPosition.x * CHUNK_LENGTH, j, k + m_ChunkPosition.z * CHUNK_LENGTH });
					}
					if (!IsPresent({ i, j - 1, k })) {
						CubeBuilder cubeBuilder;
						cubeBuilder.AddFace(Direction::Bottom);
						cubeBuilder.AddBlockType(BlockName::Dirt);
						CubeRenderer::DrawCube(cubeBuilder, { i + m_ChunkPosition.x * CHUNK_LENGTH, j, k + m_ChunkPosition.z * CHUNK_LENGTH });
					}
					continue;
				}

				CubeBuilder cubeBuilder;
				glm::i32vec3 current(i, j, k);
				if (!IsPresent(current + neighbours[(int)Direction::Front]))
					cubeBuilder.AddFace(Direction::Front);
				if (!IsPresent(current + neighbours[(int)Direction::Back]))
					cubeBuilder.AddFace(Direction::Back);
				if (!IsPresent(current + neighbours[(int)Direction::Left]))
					cubeBuilder.AddFace(Direction::Left);
				if (!IsPresent(current + neighbours[(int)Direction::Right]))
					cubeBuilder.AddFace(Direction::Right);
				if (!IsPresent(current + neighbours[(int)Direction::Top]))
					cubeBuilder.AddFace(Direction::Top);
				if (!IsPresent(current + neighbours[(int)Direction::Bottom]))
					cubeBuilder.AddFace(Direction::Bottom);
				cubeBuilder.AddBlockType(m_BlockName[i][j][k]);
				CubeRenderer::DrawCube(cubeBuilder, { i + m_ChunkPosition.x * CHUNK_LENGTH, j, k + m_ChunkPosition.z * CHUNK_LENGTH });
			}
		}
	}
}

bool Chunk::IsFaceVisible(Direction faceDirection, const glm::i32vec3& position) const
{
	switch (faceDirection)
	{
	case Direction::Front:
		break;
	case Direction::Back:
		break;
	case Direction::Left:
		break;
	case Direction::Right:
		break;
	case Direction::Top:
		if (position.y + 1 <= m_ChunkSize.y && m_BlockName[position.x][position.y + 1][position.z] == BlockName::None)
			return true;
		else
			return false;
		break;
	case Direction::Bottom:
		if (position.y - 1 >= 0 && m_BlockName[position.x][position.y - 1][position.z] == BlockName::None)
			return true;
		else
			false;
		break;
	default:
		break;
	}
}


// Checks if the block is at the outer side of the chunk and returns the direction it is exposed at
std::pair<bool, glm::i32vec3> Chunk::IsOuterBlock(const glm::i32vec3& blockPosition) const
{
	const int& x = blockPosition.x;
	const int& z = blockPosition.z;

	if (x == 0) {
		return { true, {m_ChunkPosition.x - 1, m_ChunkPosition.y, m_ChunkPosition.z} };
	}
	if (x == m_ChunkSize.x - 1) {
		return { true, {m_ChunkPosition.x + 1, m_ChunkPosition.y, m_ChunkPosition.z} };
	}
	if (z == 0) {
		return { true, {m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z - 1} };
	}
	if (z == m_ChunkSize.z - 1) {
		return { true, {m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z + 1} };
	}
	
	return { false, {} };
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
