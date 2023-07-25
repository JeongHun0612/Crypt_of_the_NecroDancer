#pragma once
#include "Skeleton.h"

class Skeleton_Normal : public Skeleton
{
private:

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Normal() {}
	~Skeleton_Normal() {}
};

