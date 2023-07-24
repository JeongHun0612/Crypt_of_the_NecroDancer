#include "Stdafx.h"
#include "Stage1_1Scene.h"

HRESULT Stage1_1Scene::init(void)
{
	GameScene::init();

	// 타일 초기화
	_vTiles = TILEMAP->getStage1Tiles();
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	_vEnemy = ENEMYMANAGER->getEnemyList();

	_tileMaxCol = MAX_STAGE1_COL;
	_tileMaxRow = MAX_STAGE1_ROW;

	// 플레이어 초기화
	PLAYER->setTile(_vTiles);
	PLAYER->setTerrainTile(_vTerrainTile);
	PLAYER->setWallTile(_vWallTile);
	PLAYER->setEnemyList(_vEnemy);
	PLAYER->setTileMaxCol(_tileMaxCol);

	// 비트 초기화
	BEAT->init();

	// 사운드 출력
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

	// 바닥 타일 타입이 계단일 시 씬 변경
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
