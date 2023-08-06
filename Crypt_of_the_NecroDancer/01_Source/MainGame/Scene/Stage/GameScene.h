#pragma once
#include "../../../2DFrameWork/GameCore/GameNode.h"

//struct Node
//{
//	Vec2 posIdx;
//	int tileIdx;
//	int alpha;
//	bool isCollider;
//};

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

	int _padeAlpha;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameScene() {}
	~GameScene() {}
};