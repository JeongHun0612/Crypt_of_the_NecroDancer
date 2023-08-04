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
	vector<Item*> _vItem;

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
	// 타일 출력
	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	// 플레이어 시야 범위
	void getShowTileBFS(vector<vector<Tile*>> vTiles, vector<Node>& vShowNode);

	// 타일 번호 출력
	void showTileNum(vector<Tile*> _vTile);
	// 플레이어에서 타일간의 거리 출력
	void showTileDist(vector<Tile*> _vTile);
	// 적 객체 
	void showEnemyCollider(vector<Tile*> _vTile);
};