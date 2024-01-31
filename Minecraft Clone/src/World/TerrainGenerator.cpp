#include "TerrainGenerator.h"

#include "FastNoiseLite/FastNoiseLite.h"

#include "AssetManager/BlockType.h"

namespace TerrainGenerator {

	void GenerateRandomTerrain(std::vector<std::vector<std::vector<BlockName>>>& chunk)
	{
		float frequency = 0.0099f;
		float cellularJitter = 0.45f; // Amplitude-like effect
		int octaves = 10;

		FastNoiseLite noise;
		noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		noise.SetSeed(42);

		noise.SetFrequency(frequency);
		noise.SetFractalOctaves(octaves);
		noise.SetCellularJitter(cellularJitter);


		for (int i = 0; i < 16; i++) {
			for (int k = 0; k < 16; k++) {
				float value = noise.GetNoise(float(i), float(k));
				float normalizedValue = (value + 1.0f) / 2.0f;
				int height = normalizedValue * 256;

				for (int j = 0; j < height; j++) {
					chunk[i][j][k] = BlockName::Dirt;
				}
			}
		}
	}

	void GenerateFlatTerrain(std::vector<std::vector<std::vector<BlockName>>>& chunk)
	{
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 256; j++) {
				for (int k = 0; k < 16; k++) {
					if (j < 3) {
						chunk[i][j][k] = BlockName::Dirt;
					}
					else {
						chunk[i][j][k] = BlockName::None;
					}
				}
			}
		}
	}

}