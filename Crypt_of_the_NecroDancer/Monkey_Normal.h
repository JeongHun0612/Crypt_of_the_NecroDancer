#pragma once
#include "Monkey.h"
class Monkey_Normal : public Monkey
{
private:

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Monkey_Normal() {}
	~Monkey_Normal() {}
};

