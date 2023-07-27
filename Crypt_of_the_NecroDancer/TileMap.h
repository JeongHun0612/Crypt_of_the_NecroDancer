#pragma once
#include "SingletonBase.h"

#define MAX_LOBBY_COL		13
#define MAX_LOBBY_ROW		15

#define MAX_STAGE1_COL		27
#define MAX_STAGE1_ROW		28

enum class TILE_TYPE
{
	TERRAIN,
	WALL,
	DECO
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
	DOOR
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

class TileMap : public SingletonBase<TileMap>
{
private:
	vector<vector<Tile*>> _vLobbyTiles;
	vector<Tile*> _vLobbyTerrain;
	vector<Tile*> _vLobbyWall;

	vector<vector<Tile*>> _vStage1Tiles;
	vector<Tile*> _vStage1Terrain;
	vector<Tile*> _vStage1Wall;

public:
	HRESULT init(void);
	void release(void);

	TileMap() {}
	~TileMap() {}

	vector<vector<Tile*>> getLoobyTiles() { return _vLobbyTiles; }
	vector<Tile*> getLoobyTerrain() { return _vLobbyTerrain; }
	vector<Tile*> getLoobyWall() { return _vLobbyWall; }

	vector<vector<Tile*>> getStage1Tiles() { return _vStage1Tiles; }
	vector<Tile*> getStage1Terrain() { return _vStage1Terrain; }
	vector<Tile*> getStage1Wall() { return _vStage1Wall; }
};

