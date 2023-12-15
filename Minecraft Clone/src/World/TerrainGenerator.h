#pragma once

#include <vector>

enum class BlockName;

namespace TerrainGenerator {

	void GenerateRandomTerrain(std::vector<std::vector<std::vector<BlockName>>>& chunk);

	void GenerateFlatTerrain(std::vector<std::vector<std::vector<BlockName>>>& chunk);

}
