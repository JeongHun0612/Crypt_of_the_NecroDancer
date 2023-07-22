#pragma once
#include "Enemy.h"

class Slime_Green : public Enemy
{
private:
	float _jumpPower;

public:
	HRESULT init(int idxY, int idxX);
	void release();
	void update();
	void render(HDC hdc);

	Slime_Green() {}
	~Slime_Green() {}
};