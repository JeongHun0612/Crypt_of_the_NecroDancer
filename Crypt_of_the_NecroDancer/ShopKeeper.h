#pragma once
#include "Enemy.h"

class ShopKeeper : public Enemy
{
private:

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	ShopKeeper() {}
	~ShopKeeper() {}
};

