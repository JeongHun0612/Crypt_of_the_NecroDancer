#pragma once
#include "Enemy.h"

class Bat_Blue : public Enemy
{
private:

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Bat_Blue() {}
	~Bat_Blue() {}
};

