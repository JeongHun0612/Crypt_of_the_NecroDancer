#pragma once
#include "Enemy.h"

class Bat_Red : public Enemy
{
private:

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>> vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	Bat_Red() {}
	~Bat_Red() {}
};

