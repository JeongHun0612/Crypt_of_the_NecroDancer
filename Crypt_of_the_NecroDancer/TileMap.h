#pragma once
#include "SingletonBase.h"

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

struct Tile
{
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
};

class TileMap : public SingletonBase<TileMap>
{
private:
	vector<Tile*> _vLobbyTerrain;
	vector<Tile*> _vLobbyWall;

	vector<Tile*> _vStage1Terrain;
	vector<Tile*> _vStage1Wall;

public:
	HRESULT init(void);
	void release(void);

	TileMap() {}
	~TileMap() {}

	vector<Tile*> getLoobyTerrain() { return _vLobbyTerrain; }
	vector<Tile*> getLoobyWall() { return _vLobbyWall; }

	vector<Tile*> getStage1Terrain() { return _vStage1Terrain; }
	vector<Tile*> getStage1Wall() { return _vStage1Wall; }
};

