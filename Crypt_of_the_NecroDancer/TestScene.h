#pragma once
#include "GameNode.h"

class TestScene : public GameNode
{
public:
	enum class PLAYER_DISTANCE
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	struct Tile
	{
		POINT imgNum;
		POINT posIdx;
		bool isColiider;
	};

private:
	RECT _player;
	POINTFLOAT _pos;
	POINT _posIdx;

	GImage* _terrainImg;
	GImage* _wallImg;

	Tile _tileTest[8][8];

	Tile _tileTerrain[30][30];
	Tile _tileWall[30][30];

	bool isMove;

	POINTFLOAT _cameraLT;
	POINTFLOAT _prevCameraLT;
	POINTFLOAT _targetPosLT;

	POINTFLOAT _posDiff;

	bool _isCameraMove;
	float _time;

	PLAYER_DISTANCE _distance;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

