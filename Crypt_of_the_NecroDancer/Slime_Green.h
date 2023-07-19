#pragma once
#include "Enemy.h"

class Slime_Green : public Enemy
{
private:

public:
	HRESULT init(int idxX, int idxY, int maxHP, int power, int coinCount);
	void release();
	void update();
	void render(HDC hdc);

	Slime_Green() {}
	~Slime_Green() {}
};