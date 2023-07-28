#pragma once
#include "Enemy.h"

class Dragon_Red : public Enemy
{
private:
	// UP / DOWN / LEFT / RIGHT
	// UP / RIGHT / DOWN / LEFT
	Vec2 _movePattern[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

	FrameImage _fireImg;
	int _firePower;
	int _fireRange;
	
	bool _isFire;
	bool _isPreFire;
	bool _isFireCoolDown;

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Dragon_Red() {}
	~Dragon_Red() {}
};

