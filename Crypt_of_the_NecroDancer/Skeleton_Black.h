#pragma once
#include "Skeleton.h"

class Skeleton_Black : public Skeleton
{
private:

public:
	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Black() {}
	~Skeleton_Black() {}
};

