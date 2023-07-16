#pragma once

#define MAX_ROBBY_COL		11
#define MAX_ROBBY_ROW		15

enum class TILE_TYPE
{
	TERRAIN,
	WALL
};

enum TERRAIN
{
	GROUND,
	STAIR,

	END
};

enum WALL
{

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
};