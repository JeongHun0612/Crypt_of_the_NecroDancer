#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Slime_Green.h"

class LobbyScene : public GameNode
{
private:
	Player _player;

	GImage* _terrainImg;
	GImage* _wallImg;

	Tile _terrainTile[MAX_TILE_ROW][MAX_TILE_COL];
	Tile _wallTile[MAX_TILE_ROW][MAX_TILE_COL];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LobbyScene() {}
	~LobbyScene() {}
};

