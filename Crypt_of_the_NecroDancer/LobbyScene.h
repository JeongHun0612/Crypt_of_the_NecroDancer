#pragma once
#include "GameScene.h"
#include "Player.h"
#include "Slime_Green.h"
#include "Slime_Blue.h"

class LobbyScene : public GameScene
{
private:
	POINT _direction[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	vector<Tile*> _vTerrainTile;
	vector<Tile*> _vWallTile;

	bool _isMove;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	HRESULT tileSet(vector<Tile*> &_vTile, TILE_TYPE type);

	LobbyScene() {}
	~LobbyScene() {}
};

