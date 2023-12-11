#pragma once

#include <glm/glm.hpp>

#include "Graphics/Shapes/Builder/CubeBuilder.h"

class CubeRenderer{
public:
	static void AddCube(CubeBuilder cubeBuilder, glm::vec3 position);

	static void Init();
	static void Shutdown();


	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	struct Stats
	{
		uint32_t CubeCount = 0;
		uint32_t DrawCount = 0;
	};
	static const Stats& GetStats();
	static void ResetStats();
};
