#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Constants.h"
#include "AssetManager/BlockType.h"

class Chunk
{
public:
	Chunk(glm::i32vec3 chunkPosition);
	~Chunk();

	bool IsVisible(glm::i32vec3 position) const;
	bool IsPresent(glm::i32vec3 position) const;
	void Render() const;

	inline glm::i32vec3 GetChunkPosition() { return m_ChunkPosition; }
private:
	glm::i32vec3 m_ChunkPosition;
	glm::i32vec3 m_ChunkSize;
	std::vector<std::vector<std::vector<BlockName>>> m_BlockName{ CHUNK_SIZE_X, std::vector<std::vector<BlockName>> {CHUNK_SIZE_Y, std::vector<BlockName> {CHUNK_SIZE_Z}} };
};
