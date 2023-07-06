#pragma once
#include "GameNode.h"

class Slime : public GameNode
{
protected:
	GImage* _img;
	POINT _pos;
	int _heart;
	int _count;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	Slime() {}
	~Slime() {}
};

