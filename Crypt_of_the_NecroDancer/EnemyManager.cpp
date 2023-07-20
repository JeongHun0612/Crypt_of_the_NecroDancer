#include "Stdafx.h"
#include "EnemyManager.h"
#include "FileManager.h"

#include "Slime_Green.h"
#include "Slime_Blue.h"
#include "Skeleton_Normal.h"
#include "Skeleton_Black.h"

HRESULT EnemyManager::init(void)
{
	FileManager::loadEnemyFile("Stage1-1_Enemy.txt", _vEnemy);

	return S_OK;
}

void EnemyManager::release(void)
{
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		delete(*iter);
	}
}
