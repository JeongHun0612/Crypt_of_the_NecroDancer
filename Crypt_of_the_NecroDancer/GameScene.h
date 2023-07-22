#pragma once
#include "GameNode.h"

class GameScene : public GameNode
{
protected:
	vector<vector<Tile*>> _vTiles;
	vector<Tile*> _vTerrainTile;
	vector<Tile*> _vWallTile;

	vector<Enemy*> _vEnemy;

	int _tileMaxCol;
	int _tileMaxRow;

	bool _isLobby;

public:
	HRESULT init(void);
	HRESULT init(int startIdxX, int startIxY, vector<vector<Tile*>> tiles, int tileMaxCol);
	void release(void);
	void update(void);
	void render(void);

	GameScene() {}
	~GameScene() {}

protected:
	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	void showTileNum(vector<Tile*> _vTile);
	void showTileDist(vector<Tile*> _vTile);

	int getAlphaSet(int distance, int rightPower);
};