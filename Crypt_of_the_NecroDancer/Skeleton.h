#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{
private:
	int _moveDirection;

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton() {}
	~Skeleton() {}
};

