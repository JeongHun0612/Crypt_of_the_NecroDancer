#pragma once

#define MAX_ROBBY_COL		11
#define MAX_ROBBY_ROW		15

enum class TILE_TYPE
{
	TERRAIN,
	WALL,
	DECO
};

enum class TERRAIN
{
	GROUND,
	STAIR,

	END
};

enum class WALL
{
	NONE,
	DIRT,
	BRICK,
	STONE,
	STEEL
};

struct Tile
{
	TERRAIN terrain;
	WALL wall;

	int idxX, idxY;
	int frameX, frameY;

	int hardness;

	bool isExist;
	bool isColiider;
	bool isLight;
};

struct Enemy
{
	int idxX, idxY;
};
