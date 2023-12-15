#pragma once

#include <glm/glm.hpp>

#include <unordered_set>

#include "Chunk.h"

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Simple hash combining technique
        return h1 ^ h2;
    }
};

class ChunkManager
{
public:
	ChunkManager(int renderDistance);
	~ChunkManager();

	void Update(glm::vec3 playerPosition);
	bool IsChunkLoaded(int chunkX, int chunkZ) const;
	void Render();
private:
	int m_RenderDistance;
	std::vector<Chunk> m_Chunks;
	std::unordered_set<std::pair<int, int>, PairHash> m_LoadedChunks;
private:
	void LoadChunks(glm::vec3 playerPosition);
	void UnloadChunks(glm::vec3 playerPosition);
	void LoadChunk(int chunkIndexX, int chunkIndexZ);
	void UnloadChunk(int chunkX, int chunkZ);
};
