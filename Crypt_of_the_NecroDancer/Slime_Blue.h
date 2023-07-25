#pragma once
#include "Enemy.h"

class Slime_Blue : public Enemy
{
private:
	Vec2 _movePattern[2] = { {0, -1}, {0, 1} };

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Slime_Blue() {}
	~Slime_Blue() {}
};

