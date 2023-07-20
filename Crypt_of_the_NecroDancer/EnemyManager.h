#pragma once
#include "SingletonBase.h"

class Enemy;

enum ENEMY_TYPE
{
	SLIME_GREE,
	SLIME_BLUE,
	SKELETON_NORMAL,
	SKELETON_BLACK
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

