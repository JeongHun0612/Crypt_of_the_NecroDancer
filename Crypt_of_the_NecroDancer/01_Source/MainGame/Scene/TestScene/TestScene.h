#pragma once
#include "../Stage/GameScene.h"

class TestScene : public GameScene
{
public:
	struct Node
	{
		Vec2 posIdx;
		int tileIdx;
		int alpha;
		bool isCollider;
	};

private:
	//vector<int> _drawTileIdx;
	//unordered_set<int> _drawTileIdx;
	queue<int> _drawTileIdx;
	vector<Node> _drawNode;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//vector<Node> tileSetTest(vector<vector<Tile*>> vTiles);
	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	TestScene() {}
	~TestScene() {}
};

