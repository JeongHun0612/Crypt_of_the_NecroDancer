#pragma once
#include "GameNode.h"

enum class GAME_SCENE_TYPE
{
	STAGE1_1,
	STAGE1_2,
	STAGE1_BOSS,

	END
};

class GameScene : public GameNode
{
protected:
	vector<vector<Tile*>> _vTiles;
	vector<Tile*> _vTerrainTile;
	vector<Tile*> _vWallTile;

	vector<Enemy*> _vEnemy;

	GAME_SCENE_TYPE _curGameScene;

	int _tileMaxCol;
	int _tileMaxRow;
	
	bool _isLobby;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameScene() {}
	~GameScene() {}

protected:
	void tileSet(vector<Tile*> vTile, TILE_TYPE tileType);

	void showTileNum(vector<Tile*> _vTile);
	void showTileDist(vector<Tile*> _vTile);

	int getAlphaSet(int distance, int rightPower);
};