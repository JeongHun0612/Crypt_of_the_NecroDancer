#pragma once

#define MAX_LOBBY_COL		11
#define MAX_LOBBY_ROW		15

#define MAX_STAGE1_COL		31
#define MAX_STAGE1_ROW		25

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

class Tile
{
private:
	TERRAIN _terrain;
	WALL _wall;

	int _idxX;
	int _idxY;

	int _frameX;
	int _frameY;

	int _hardNess;

	bool _isExist;
	bool _isCollider;
	bool _isLight;

public:
	HRESULT init(int idxX, int idxY, int frameX, int frameY, bool isCollider, bool isExist, int hardNess, TERRAIN terrain);
	HRESULT init(int idxX, int idxY, int frameX, int frameY, bool isCollider, bool isExist, int hardNess, WALL wall);

	int getIdxX() { return _idxX; }
	int getIdxY() { return _idxY; }
	int getFrameX() { return _frameX; }
	int getFrameY() { return _frameY; }
	bool getIsCollider() { return _isCollider; }
	bool getIsExist() { return _isExist; }
	bool getIsLight() { return _isLight; }
	int getHardNess() { return _hardNess; }

	void setIsCollider(bool isCollider) { _isCollider = isCollider; }
	void setIsExist(bool isExist) { _isExist = isExist; }
	void setIsLight(bool isLight) { _isLight = isLight; }

	TERRAIN getTerrain() { return _terrain; }
	WALL getWall() { return _wall; }
};

