#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
private:
	Vec2 _movePattern[2] = { {1, 0}, {-1, 0} };

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Zombie() {}
	~Zombie() {}
};

