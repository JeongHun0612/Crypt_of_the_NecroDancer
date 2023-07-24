#pragma once
#include "Enemy.h"

class Slime_Blue : public Enemy
{
private:

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	bool _isUp;

	Slime_Blue() {}
	~Slime_Blue() {}
};

