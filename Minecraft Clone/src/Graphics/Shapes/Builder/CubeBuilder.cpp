#include "CubeBuilder.h"

#include "../Cube.h"

CubeBuilder::CubeBuilder()
{
	memset(VisibleFaces, 0, sizeof(VisibleFaces));
}

CubeBuilder::~CubeBuilder()
{
}

void CubeBuilder::AddFaces(Direction direction)
{
	VisibleFaces[(int)direction] = true;
}

