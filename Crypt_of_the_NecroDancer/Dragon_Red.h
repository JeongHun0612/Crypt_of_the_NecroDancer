#pragma once
#include "Enemy.h"

class Dragon_Red : public Enemy
{
private:
	int _firePower;

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Dragon_Red() {}
	~Dragon_Red() {}
};

