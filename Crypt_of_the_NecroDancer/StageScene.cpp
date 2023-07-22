#include "Stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init(void)
{
	// 비트 초기화
	BEAT->init();

	// 타일 초기화
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	// 애너미 초기화
	_vEnemy = ENEMYMANAGER->getEnemyList();

	// 사운드 플레이
	SOUNDMANAGER->play("stage1-1", 0.5f);

	return S_OK;
}

void StageScene::release(void)
{
	SOUNDMANAGER->stop("stage1-1");
}

void StageScene::update(void)
{
	CAMERA->update();
	PLAYER->update();
	BEAT->update();
}

void StageScene::render(void)
{
	// 타일 출력
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// 플레이어 출력
	PLAYER->render(getMemDC());

	// 몬스터 출력
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// 디버그 모드
	if (KEYMANAGER->isToggleKey(VK_F1) && !_vTerrainTile.empty())
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2) && !_vTerrainTile.empty())
	{
		showTileDist(_vTerrainTile);
	}

	// 비트 출력
	BEAT->render(getMemDC());

	// UI 출력
	UIMANAGER->render(getMemDC());
}