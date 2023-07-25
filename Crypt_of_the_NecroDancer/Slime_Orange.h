#pragma once
#include "Enemy.h"

class Slime_Orange : public Enemy
{
private:
	Vec2 _movePattern[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Slime_Orange() {}
	~Slime_Orange() {}
};

