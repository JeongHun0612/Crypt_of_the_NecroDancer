#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Slime_Green.h"

#define MAX_ROBBY_COL		11
#define MAX_ROBBY_ROW		15

class LobbyScene : public GameNode
{
private:
	GImage* _terrainImg;
	GImage* _wallImg;

	Tile _terrainTile[MAX_ROBBY_ROW][MAX_ROBBY_COL];
	Tile _wallTile[MAX_ROBBY_ROW][MAX_ROBBY_COL];

	vector<Tile> _vTerrainTile;
	vector<vector<Tile>> _vTiles;

	Tile _testTile[5][6];
	float _time;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LobbyScene() {}
	~LobbyScene() {}
};

