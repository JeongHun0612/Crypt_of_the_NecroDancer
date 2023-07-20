#pragma once
#include "SingletonBase.h"
#include "Tile.h"

// 세로 13 x 가로 19 (Winsize 범위)
#define INSPRECTION_RANGE	247

class TileMap : public SingletonBase<TileMap>
{
private:
	int _startIdx;

	vector<Tile> _vLobbyTerrain;
	vector<Tile> _vLobbyWall;

	vector<Tile> _vStage1Terrain;
	vector<Tile> _vStage1Wall;

public:
	HRESULT init(void);
	void release(void);

	TileMap() {}
	~TileMap() {}

	int getStartIdx() { return _startIdx; }
	void setStartIdx(int playerIdxX, int playerIdxY, int max_col);

	vector<Tile>& getLoobyTerrain() { return _vLobbyTerrain; }
	vector<Tile>& getLoobyWall() { return _vLobbyWall; }

	vector<Tile>& getStage1Terrain() { return _vStage1Terrain; }
	vector<Tile>& getStage1Wall() { return _vStage1Wall; }
};

