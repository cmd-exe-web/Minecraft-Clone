#pragma once

enum class BlockName {
	Dirt, Cobblestone
};

struct Face {
	float Left = 0, Right = 0, Top = 0, Bottom = 0;
};

struct TextureAtlas {
	Face Top, Sides, Base;
};
