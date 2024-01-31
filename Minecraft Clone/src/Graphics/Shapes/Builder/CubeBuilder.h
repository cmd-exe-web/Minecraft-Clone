#pragma once

#include "AssetManager/BlockType.h"

enum class Direction
{
	Front = 0, Back, Left, Right, Top, Bottom
};

class Cube;

class CubeBuilder
{
public:
	CubeBuilder();
	~CubeBuilder();

	void AddFace(Direction direction);
	void AddBlockType(BlockName name);
	bool VisibleFaces[6];
	BlockName Name;
};
