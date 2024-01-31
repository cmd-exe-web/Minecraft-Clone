#pragma once

class ChunkManager;

#include <vector>

#include "glm/glm.hpp"

#include "Constants.h"
#include "AssetManager/BlockType.h"

enum class Direction;

class Chunk
{
public:
	Chunk(glm::i32vec3 chunkPosition);
	~Chunk();

	std::pair<bool, glm::i32vec3> IsOuterBlock(const glm::i32vec3& blockPosition) const;
	bool IsVisible(glm::i32vec3 position) const;
	bool IsPresent(glm::i32vec3 position) const;
	void Render(ChunkManager& chunkManager) const;
	inline glm::i32vec3 GetChunkPosition() const { return m_ChunkPosition; }
private:
	glm::i32vec3 m_ChunkPosition;
	glm::i32vec3 m_ChunkSize;
	std::vector<std::vector<std::vector<BlockName>>> m_BlockName{ CHUNK_SIZE_X, std::vector<std::vector<BlockName>> {CHUNK_SIZE_Y, std::vector<BlockName> {CHUNK_SIZE_Z}} };

private:
	bool IsFaceVisible(Direction faceDirection, const glm::i32vec3& position) const;
};
