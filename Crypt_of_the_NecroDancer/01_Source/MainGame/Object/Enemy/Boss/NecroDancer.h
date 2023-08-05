#pragma once
#include "../Enemy.h"

enum SKILL_PATTERN
{
	MINIBOSS_SUMMON,
	ICE,
	EXPLOSION
};

class NecroDancer : public Enemy
{
private:
	Vec2 _movePattern[8] = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };
	Vec2 _centerPos = { 8, 11 };

	MoveInfo _bossMoveInfo[8];

	int _moveCnt;

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	NecroDancer() {}
	~NecroDancer() {}
};

