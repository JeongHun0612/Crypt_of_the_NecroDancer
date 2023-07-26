#pragma once
#include "GameScene.h"

struct Node
{
	int depth;
};

class TestScene : public GameScene
{
private:
	//vector<int> _drawTileIdx;
	unordered_set<int> _drawTileIdx;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	unordered_set<int> tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	TestScene() {}
	~TestScene() {}
};

