#pragma once
#include "../../Enemy.h"

class Minotaur_Normal : public Enemy
{
private:
	bool _isCharge;
	bool _isGroggy;

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	Minotaur_Normal() {}
	~Minotaur_Normal() {}

};

