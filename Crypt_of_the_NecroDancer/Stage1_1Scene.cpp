#include "Stdafx.h"
#include "Stage1_1Scene.h"

HRESULT Stage1_1Scene::init(void)
{
	GameScene::init();

	// Ÿ�� �ʱ�ȭ
	_vTiles = TILEMAP->getStage1Tiles();
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	_vEnemy = ENEMYMANAGER->getEnemyList();

	_tileMaxCol = MAX_STAGE1_COL;
	_tileMaxRow = MAX_STAGE1_ROW;

	// �÷��̾� �ʱ�ȭ
	PLAYER->setTile(_vTiles);
	PLAYER->setTerrainTile(_vTerrainTile);
	PLAYER->setWallTile(_vWallTile);
	PLAYER->setEnemyList(_vEnemy);
	PLAYER->setTileMaxCol(_tileMaxCol);

	// ��Ʈ �ʱ�ȭ
	BEAT->init();

	// ���� ���
	SOUNDMANAGER->play("stage1-1", 0.5f);

	return S_OK;
}

void Stage1_1Scene::release(void)
{
	SOUNDMANAGER->stop("stage1-1");
}

void Stage1_1Scene::update(void)
{
	GameScene::update();

	// �ٴ� Ÿ�� Ÿ���� ����� �� �� ����
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::STAIR)
	{
		//SCENEMANAGER->changeScene("game");
	}
}

void Stage1_1Scene::render(void)
{
	GameScene::render();
}
