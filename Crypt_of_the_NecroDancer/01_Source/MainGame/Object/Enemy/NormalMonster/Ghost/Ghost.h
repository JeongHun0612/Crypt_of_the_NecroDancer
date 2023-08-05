#pragma once
#include "../../Enemy.h"

class Ghost : public Enemy
{
private:

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	Ghost() {}
	~Ghost() {}
};

