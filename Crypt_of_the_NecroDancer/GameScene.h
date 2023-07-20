#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Tile.h"
#include "Slime_Green.h"
#include "Slime_Blue.h"
#include "Skeleton_normal.h"

class GameScene : public GameNode
{
private:
	vector<Tile> _vTerrainTile;
	vector<Tile> _vWallTile;

	vector<Enemy*> _vEnemy;

	bool _isMove;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameScene() {}
	~GameScene() {}

private:
	HRESULT tileSet(vector<Tile>& _vTile, TILE_TYPE type);

	void enemySet();

	int getAlphaSet(int distance, int rightPower);

	void showTileNum(vector<Tile> _vTile);
	void showTileDist(vector<Tile> _vTile);
};