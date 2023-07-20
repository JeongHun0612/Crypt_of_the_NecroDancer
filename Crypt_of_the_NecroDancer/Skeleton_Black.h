#pragma once
#include "Enemy.h"

class Skeleton_Black : public Enemy
{
private:

public:
	HRESULT init(int idxY, int idxX);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Black() {}
	~Skeleton_Black() {}
};

