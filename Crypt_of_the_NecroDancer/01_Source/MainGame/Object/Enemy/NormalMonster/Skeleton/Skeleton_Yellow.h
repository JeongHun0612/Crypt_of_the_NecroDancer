#pragma once
#include "Skeleton.h"

class Skeleton_Yellow : public Skeleton
{
private:

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	Skeleton_Yellow() {}
	~Skeleton_Yellow() {}
};

