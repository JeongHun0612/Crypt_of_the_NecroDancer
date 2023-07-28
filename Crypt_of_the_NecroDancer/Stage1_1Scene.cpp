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

	// 다음 스테이지 계단
	_stairTileIdx = 22 * _tileMaxCol + 4;

	// 플레이어 초기화
	PLAYER->setPosIdx(13, 10);
	PLAYER->setNextPosIdx(13, 10);
	PLAYER->setTile(_vTiles);
	PLAYER->setTerrainTile(_vTerrainTile);
	PLAYER->setWallTile(_vWallTile);
	PLAYER->setEnemyList(_vEnemy);
	PLAYER->setTileMaxCol(_tileMaxCol);

	// 비트 초기화
	BEAT->init();
	//BEAT->setIsBeat(true);

	// 사운드 출력
	SOUNDMANAGER->play("stage1_1", 0.5f);
	SOUNDMANAGER->play("stage1_1_shopkeeper", 0.5f);

	return S_OK;
}

void Stage1_1Scene::release(void)
{
	SOUNDMANAGER->stop("stage1_1");
	SOUNDMANAGER->stop("stage1_1_shopkeeper");
}

void Stage1_1Scene::update(void)
{
	GameScene::update();

	if (PLAYER->getIsNextStage())
	{
		_vTerrainTile[_stairTileIdx]->_frameY = 0;
	}

	// 바닥 타일 타입이 계단일 시 씬 변경
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::STAIR && PLAYER->getIsNextStage())
	{
		cout << "다음 씬 전환" << endl;
		//SCENEMANAGER->changeScene("game");
	}
}

void Stage1_1Scene::render(void)
{
	GameScene::render();
}
