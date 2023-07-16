#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Slime_Green.h"
#include "TileNode.h"

class LobbyScene : public GameNode
{
private:
	GImage* _terrainImg;
	GImage* _wallImg;

	Tile _terrainTile[MAX_ROBBY_ROW][MAX_ROBBY_COL];
	Tile _wallTile[MAX_ROBBY_ROW][MAX_ROBBY_COL];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void tileSet(Tile _tile[][MAX_ROBBY_COL], TILE_TYPE type);

	LobbyScene() {}
	~LobbyScene() {}
};

