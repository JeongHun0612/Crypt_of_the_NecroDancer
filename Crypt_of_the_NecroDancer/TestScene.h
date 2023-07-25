#pragma once
#include "GameScene.h"

class TestScene : public GameScene
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	TestScene() {}
	~TestScene() {}
};

