#pragma once
#include "Slime.h"

class Slime_Blue : public Slime
{
private:

public:
	HRESULT init(int idxX, int idxY, int maxHP, int power, int coinCount);
	void release();
	void update();
	void render(HDC hdc);

	bool _isUp;

	Slime_Blue() {}
	~Slime_Blue() {}
};

