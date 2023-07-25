#pragma once
#include "Enemy.h"

class Monkey : public Enemy
{
private:
	GImage* _grabImg;
	bool _isGrab;

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Monkey() {}
	~Monkey() {}
};

