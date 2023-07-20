#pragma once
#include "Enemy.h"

class Skeleton_Normal : public Enemy
{
private:
	int moveDirection;
	int prevMoveDirection;

	int minDistance;

	int distance[4];

public:
	HRESULT init(int idxY, int idxX);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Normal() {}
	~Skeleton_Normal() {}
};

