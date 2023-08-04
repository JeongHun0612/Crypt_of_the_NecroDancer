#pragma once

#define MAX_LOBBY_COL		13
#define MAX_LOBBY_ROW		15

#define MAX_STAGE1_1_COL		27
#define MAX_STAGE1_1_ROW		28

#define MAX_STAGE1_2_COL		34
#define MAX_STAGE1_2_ROW		26

enum class TILE_TYPE
{
	TERRAIN,
	WALL,
	DECO
};

enum class ENEMY_TYPE
{
	SLIME_GREEN,
	SLIME_BLUE,
	SLIME_ORANGE,
	SKELETON_NORMAL,
	SKELETON_YELLOW,
	SKELETON_BLACK,
	ZOMBIE,
	BAT_BLUE,
	BAT_RED,
	MONKEY_NORMAL,
	MONKEY_WHITE,
	GHOST,
	WRAITH,
	MINOTAUR_NORMAL,
	DRAGON_RED,

	SHOPKEEPER = 16
};

enum class TERRAIN_TYPE
{
	GROUND,
	STAIR,

	END
};

enum class WALL_TYPE
{
	NONE,
	DIRT,
	BRICK,
	STONE,
	STEEL,
	BORDER,
	DOOR,
	GOLDWALL
};

struct Tile
{
	TERRAIN_TYPE _terrainType;
	WALL_TYPE _wallType;

	int _idxX;
	int _idxY;

	int _frameX;
	int _frameY;

	int _alpha;
	int _hardNess;

	bool _isExist;
	bool _isCollider;
	bool _isSearch;
	bool _isLight;
};