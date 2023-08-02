#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
protected:
	AlphaImage _headImg;

	int _moveCount;

	int _prevMoveDirection;
	int _headMoveDirection;

	bool _isCollider;
	bool _isNoHead;
	bool _isHeadMove;

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>> vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton() {}
	~Skeleton() {}
};

