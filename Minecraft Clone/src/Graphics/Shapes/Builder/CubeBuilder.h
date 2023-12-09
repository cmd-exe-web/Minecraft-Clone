#pragma once

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

	void AddFaces(Direction direction);
	Cube Build();
	bool VisibleFaces[6];
};
