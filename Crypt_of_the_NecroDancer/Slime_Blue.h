#pragma once
#include "Slime.h"

class Slime_Blue : public Slime
{
private:

public:
	HRESULT init(int idxX, int idxY, int heart);
	void release();
	void update();
	void render(HDC hdc);

	Slime_Blue() {}
	~Slime_Blue() {}
};

