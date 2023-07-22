#pragma once
#include "Enemy.h"

struct Distance
{
	int distance;
	int direction;
};

class Skeleton_Normal : public Enemy
{
private:
	Distance _FourDistacne[4];

public:
	HRESULT init(int idxY, int idxX);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Normal() {}
	~Skeleton_Normal() {}
};

