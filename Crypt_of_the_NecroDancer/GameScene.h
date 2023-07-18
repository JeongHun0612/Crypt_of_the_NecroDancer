#pragma once
#include "GameNode.h"
#include "Player.h"
#include "TileNode.h"
#include "Slime_Green.h"
#include "Slime_Blue.h"

class GameScene : public GameNode
{
private:
	GImage* _terrainImg;
	GImage* _wallImg;

	PLAYER_DIRECTION _nextDirection;

	vector<Slime*> _vSlime;

	vector<Tile> _vTerrainTile;
	vector<Tile> _vWallTile;

	Enemy _enemyTile[MAX_ROBBY_ROW][MAX_ROBBY_COL];

	bool _isMove;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void tileSet(vector<Tile>& _vTile, TILE_TYPE type);
	void enemySet();
	int getAlphaSet(int distance, int rightPower);

	void showTileNum(vector<Tile> _vTile);
	void showTileDist(vector<Tile> _vTile);
};

