#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Slime_Green.h"

#define MAX_TILE_COL		50
#define MAX_TILE_ROW		50

class LobbyScene : public GameNode
{
public:
	struct Tile
	{
		POINT imgNum;
		POINT posIdx;
		POINT size;
		RECT rc;
	};

	struct Camera
	{
		float x, y;
	};

private:
	Player _player;

	GImage* _tileImg;
	Tile _tile[MAX_TILE_ROW][MAX_TILE_COL];

	Camera _camera;

	float _count;
	
	int testCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LobbyScene() {}
	~LobbyScene() {}
};

