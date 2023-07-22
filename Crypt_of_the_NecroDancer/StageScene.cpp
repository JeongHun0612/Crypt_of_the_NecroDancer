#include "Stdafx.h"
#include "StageScene.h"

HRESULT StageScene::init(void)
{
	// ��Ʈ �ʱ�ȭ
	BEAT->init();

	// Ÿ�� �ʱ�ȭ
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	// �ֳʹ� �ʱ�ȭ
	_vEnemy = ENEMYMANAGER->getEnemyList();

	// ���� �÷���
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
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// ���� ���
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// ����� ���
	if (KEYMANAGER->isToggleKey(VK_F1) && !_vTerrainTile.empty())
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2) && !_vTerrainTile.empty())
	{
		showTileDist(_vTerrainTile);
	}

	// ��Ʈ ���
	BEAT->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());
}