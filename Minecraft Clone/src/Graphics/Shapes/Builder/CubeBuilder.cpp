#include "CubeBuilder.h"

#include "../Cube.h"

CubeBuilder::CubeBuilder()
{
	memset(VisibleFaces, 0, sizeof(VisibleFaces));
}

CubeBuilder::~CubeBuilder()
{
}

void CubeBuilder::AddFace(Direction direction)
{
	VisibleFaces[(int)direction] = true;
}

void CubeBuilder::AddBlockType(BlockName name)
{
	Name = name;
}

