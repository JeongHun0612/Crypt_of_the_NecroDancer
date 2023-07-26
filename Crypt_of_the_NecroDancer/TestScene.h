#pragma once
#include "GameScene.h"

struct Node
{
	int tileIdx;
	int depth;
	bool isCollider;
};

class TestScene : public GameScene
{
private:
	//vector<int> _drawTileIdx;
	//unordered_set<int> _drawTileIdx;
	queue<int> _drawTileIdx;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	unordered_set<int> tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	TestScene() {}
	~TestScene() {}
};

