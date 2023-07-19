#pragma once
#include "Tile.h"

class TileMap
{
private:
	vector<Tile> _vLobbyTerrain;
	vector<Tile> _vLobbyWall;

	//vector<Tile> _vStage1;

public:
	HRESULT init(void);
	void release(void);

	TileMap() {}
	~TileMap() {}

	vector<Tile>& getLoobyTileMap() { return _vLobbyTerrain; }
};

