#pragma once
#include "GameNode.h"

struct Node
{
	Vec2 posIdx;
	int tileIdx;
	int alpha;
	bool isCollider;
};

class GameScene : public GameNode
{
protected:
	vector<vector<Tile*>> _vTiles;
	vector<Tile*> _vTerrainTile;
	vector<Tile*> _vWallTile;

	vector<Node> _vShowNode;

	vector<Enemy*> _vEnemy;

	int _tileMaxCol;
	int _tileMaxRow;

	int _stairTileIdx;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameScene() {}
	~GameScene() {}

protected:
	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);
	void getShowTileBFS(vector<vector<Tile*>> vTiles, vector<Node>& vShowNode);

	void showTileNum(vector<Tile*> _vTile);
	void showTileDist(vector<Tile*> _vTile);
	void showEnemyCollider(vector<Tile*> _vTile);
};