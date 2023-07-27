#pragma once
#include "Enemy.h"

class Minotaur_Normal : public Enemy
{
private:
	FrameImage _groggyImg;
	FrameImage _tempImg;

	int _chargeDirection;
	
	bool _isCharge;
	bool _isGroggy;

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Minotaur_Normal() {}
	~Minotaur_Normal() {}

};

