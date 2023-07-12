#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Slime_Green.h"

#define MAX_TILE_COL		30
#define MAX_TILE_ROW		30

class LobbyScene : public GameNode
{
public:
	struct Tile
	{
		POINT imgNum;
		POINT posIdx;
		bool isColiider;
	};

private:
	Player _player;

	GImage* _terrainImg;
	Tile _tile[MAX_TILE_ROW][MAX_TILE_COL];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LobbyScene() {}
	~LobbyScene() {}
};

