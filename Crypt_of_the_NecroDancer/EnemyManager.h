#pragma once
#include "SingletonBase.h"

class Enemy;

enum ENEMY_TYPE
{
	SLIME_GREEN,
	SLIME_BLUE,
	SLIME_ORANGE,
	SKELETON_NORMAL,
	SKELETON_YELLOW,
	SKELETON_BLACK,
	ZOMBIE,
	BAT_BLUE
};

class EnemyManager : public SingletonBase<EnemyManager>
{
private:
	vector<Enemy*> _vEnemy;

public:
	HRESULT init(void);
	void release(void);

	vector<Enemy*> getEnemyList() { return _vEnemy; }
};

