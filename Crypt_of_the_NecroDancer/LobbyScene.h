#pragma once
#include "GameNode.h"
#include "Player.h"
#include "TileNode.h"
#include "Slime_Green.h"
#include "Slime_Blue.h"

class LobbyScene : public GameNode
{
private:
	GImage* _terrainImg;
	GImage* _wallImg;

	PLAYER_DIRECTION _nextDirection;

	vector<Tile> _vTerrainTile;
	vector<Tile> _vWallTile;

	Enemy _enemyTile[MAX_ROBBY_ROW][MAX_ROBBY_COL];

	bool _isMove;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void tileSet(vector<Tile> &_vTile, TILE_TYPE type);

	LobbyScene() {}
	~LobbyScene() {}
};

