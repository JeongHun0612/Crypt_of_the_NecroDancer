#pragma once
#include "Enemy.h"

class Skeleton_Normal : public Enemy
{
private:


public:
	HRESULT init(int idxX, int idxY, int maxHP, int power, int coinCount);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Normal() {}
	~Skeleton_Normal() {}
};

