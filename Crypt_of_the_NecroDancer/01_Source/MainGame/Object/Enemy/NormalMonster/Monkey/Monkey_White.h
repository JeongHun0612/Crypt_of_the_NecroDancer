#pragma once
#include "Monkey.h"

class Monkey_White : public Monkey
{
private:

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	Monkey_White() {}
	~Monkey_White() {}
};

