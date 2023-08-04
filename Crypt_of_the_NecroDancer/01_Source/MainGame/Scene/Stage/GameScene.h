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
	// Ÿ�� ���
	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	// �÷��̾� �þ� ����
	void getShowTileBFS(vector<vector<Tile*>> vTiles, vector<Node>& vShowNode);

	// Ÿ�� ��ȣ ���
	void showTileNum(vector<Tile*> _vTile);
	// �÷��̾�� Ÿ�ϰ��� �Ÿ� ���
	void showTileDist(vector<Tile*> _vTile);
	// �� ��ü 
	void showEnemyCollider(vector<Tile*> _vTile);
};