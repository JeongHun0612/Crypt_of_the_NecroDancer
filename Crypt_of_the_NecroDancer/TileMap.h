#pragma once
#include "SingletonBase.h"
#include "Tile.h"

class TileMap : public SingletonBase<TileMap>
{
private:
	vector<Tile> _vLobbyTerrain;
	vector<Tile> _vLobbyWall;

	vector<Tile> _vStage1Terrain;
	vector<Tile> _vStage1Wall;

public:
	HRESULT init(void);
	void release(void);

	TileMap() {}
	~TileMap() {}

	vector<Tile>& getLoobyTerrain() { return _vLobbyTerrain; }
	vector<Tile>& getLoobyWall() { return _vLobbyWall; }

	vector<Tile>& getStage1Terrain() { return _vStage1Terrain; }
	vector<Tile>& getStage1Wall() { return _vStage1Wall; }
};

