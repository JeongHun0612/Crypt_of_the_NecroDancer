#pragma once
#include "../Enemy.h"

enum SKILL_PATTERN
{
	MINIBOSS_SUMMON,
	ICE_BLAST,
	EXPLOSION
};

class NecroDancer : public Enemy
{
private:
	FrameImage _explosionImg;
	FrameImage _iceBlastImg;

	Vec2 _movePattern[8] = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };
	Vec2 _explosionRange[24] = { 
		{-2, -2}, {-1, -2}, {0, -2}, {1, -2}, {2, 2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, {-1, 2}, {-2, 2}, {-2, 0}, {-2, -1},
		{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0},
		{0, 0}};

	Vec2 _iceBalstRange[18] = {
		{-3,-2}, {-3, -1}, {-3, 0}, {-3, 1}, {-3, 2}, {-2, -1}, {-2, 0}, {-2, 1}, {-1, 0},
		{3,2}, {3, 1}, {3, 0}, {3, 1}, {3, 2}, {2, -1}, {2, 0}, {2, 1}, {1, 0} };

	Vec2 _centerPos = { 8, 11 };

	MoveInfo _bossMoveInfo[8];
	Enemy* _summonEnemy;

	int _moveCnt;
	int _miniBossCnt;
	int _skillPattern;

	bool _isSkill;
	bool _isExplosion;
	bool _isIceBlast;

public:
	HRESULT init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol);
	void release();
	void update();
	void render(HDC hdc);

	NecroDancer() {}
	~NecroDancer() {}
};

