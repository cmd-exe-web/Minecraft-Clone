#include "ChunkManager.h"

#include "Graphics/Renderer/CubeRenderer.h"

ChunkManager::ChunkManager(int renderDistance)
	:m_RenderDistance(renderDistance)
{
	m_LoadedChunks.clear();
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::LoadChunks(glm::vec3 playerPosition)
{
	int playerChunkX = (int)playerPosition.x / 16;
	int playerChunkZ = (int)playerPosition.z / 16;

	for (int xOffset = -m_RenderDistance; xOffset <= m_RenderDistance; xOffset++) {
		for (int zOffset = -m_RenderDistance; zOffset <= m_RenderDistance; zOffset++) {
			int chunkX = playerChunkX + xOffset;
			int chunkY = playerChunkZ + zOffset;
			if(!IsChunkLoaded(chunkX, chunkY))
				LoadChunk(chunkX, chunkY);
		}
	}
}

void ChunkManager::UnloadChunks(glm::vec3 playerPosition)
{
	int playerChunkX = (int)playerPosition.x / 16;
	int playerChunkZ = (int)playerPosition.z / 16;
	for (auto it = m_LoadedChunks.begin();
		it != m_LoadedChunks.end(); /* No increment here */) {
		int chunkX = it->first;
		int chunkZ = it->second;

		if (std::abs(chunkX - playerChunkX) > m_RenderDistance || std::abs(chunkZ - playerChunkZ) > m_RenderDistance) {
			auto validIterator = m_LoadedChunks.erase(it);
			UnloadChunk(chunkX, chunkZ);
			it = validIterator;
		}
		else {
			it++;
		}
	}
}

void ChunkManager::LoadChunk(int chunkIndexX, int chunkIndexZ)
{
	m_Chunks.emplace_back(Chunk({ chunkIndexX, 0, chunkIndexZ }));
	m_LoadedChunks.insert({ chunkIndexX, chunkIndexZ });
}

void ChunkManager::UnloadChunk(int chunkX, int chunkZ)
{
	for (int i = 0; i < m_Chunks.size(); i++)
	{
		auto chunkPosition = m_Chunks[i].GetChunkPosition();
		if (chunkPosition.x == chunkX && chunkPosition.z == chunkZ) {
			m_Chunks.erase(m_Chunks.begin() + i);
			i--;
		}
	}
}

void ChunkManager::Update(glm::vec3 playerPosition)
{
	LoadChunks(playerPosition);
	UnloadChunks(playerPosition);
}

bool ChunkManager::IsChunkLoaded(int chunkX, int chunkZ) const
{
	return m_LoadedChunks.find({ chunkX, chunkZ }) != m_LoadedChunks.end();
}

void ChunkManager::Render()
{
	for (const auto& chunk : m_Chunks) {
		chunk.Render(*this);
	}
}
