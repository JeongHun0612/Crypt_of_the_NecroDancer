#include "Stdafx.h"
#include "EnemyManager.h"
#include "Slime_Green.h"
#include "Slime_Blue.h"
#include "Skeleton_Normal.h"
#include "Skeleton_Black.h"

HRESULT EnemyManager::init(void)
{
	// 애너미 초기화
	Enemy* _slime = new Slime_Green;
	_slime->init(3, 3, 1, 0, 3);

	_vEnemy.push_back(_slime);

	Enemy* _slime2 = new Slime_Blue;
	_slime2->init(3, 5, 2, 1, 4);

	_vEnemy.push_back(_slime2);

	Enemy* _skeleton1 = new Skeleton_Normal;
	_skeleton1->init(6, 5, 1, 1, 3);

	_vEnemy.push_back(_skeleton1);

	Enemy* _skeleton2 = new Skeleton_Black;
	_skeleton2->init(6, 6, 3, 2, 5);

	_vEnemy.push_back(_skeleton2);

	return S_OK;
}

void EnemyManager::release(void)
{
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		delete(*iter);
	}
}
