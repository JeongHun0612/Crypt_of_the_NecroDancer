#pragma once
#include "SingletonBase.h"

class Enemy;

class EnemyManager : public SingletonBase<EnemyManager>
{
private:
	vector<Enemy*> _vEnemy;

public:
	HRESULT init(void);
	void release(void);


	vector<Enemy*> getEnemyList() { return _vEnemy; }
};

