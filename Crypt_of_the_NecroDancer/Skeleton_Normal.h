#pragma once
#include "Enemy.h"

struct MoveInfo
{
	int direction;
	int distance;
};

class Skeleton_Normal : public Enemy
{
private:
	MoveInfo _moveInfo[4];
	int _moveDirection;

public:
	HRESULT init(int idxY, int idxX);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Normal() {}
	~Skeleton_Normal() {}
};

