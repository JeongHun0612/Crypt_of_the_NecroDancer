#pragma once
#include "Slime.h"

class Slime_Green : public Slime
{
private:

public:
	HRESULT init(POINT pos, int heart);
	void release();
	void update();
	void render();

	Slime_Green() {}
	~Slime_Green() {}
};

