#pragma once
#include "Enemy.h"

class Monkey : public Enemy
{
protected:
	int _grabMaxHP;

	bool _isGrab;
	bool _isKnockBack;

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Monkey() {}
	~Monkey() {}
};

