#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "Stage1_2Scene.h"

HRESULT Stage1_2Scene::init(void)
{
	GameScene::init();

	// 타일 초기화
	FileManager::loadTileMapFile("Stage1_2_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1_2_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	_vTiles.push_back(_vTerrainTile);
	_vTiles.push_back(_vWallTile);

	_tileMaxCol = MAX_STAGE1_2_COL;
	_tileMaxRow = MAX_STAGE1_2_ROW;

	// 애너미 초기화
	FileManager::loadEnemyFile("Stage1_2_Enemy.txt", _vEnemy, _vTiles, _tileMaxCol);

	// 다음 스테이지 계단
	_stairTileIdx = 20 * _tileMaxCol + 4;

	// 플레이어 초기화
	PLAYER->init(13, 5, _vEnemy, _vItem, _vTiles, _tileMaxCol);

	// 비트 초기화
	BEAT->init("stage1_3.txt", "stage1_3");

	// 사운드 출력
	SOUNDMANAGER->play("stage1_3");
	SOUNDMANAGER->play("stage1_3_shopkeeper");

	return S_OK;
}

void Stage1_2Scene::release(void)
{
	SOUNDMANAGER->stop("stage1_3");
	SOUNDMANAGER->stop("stage1_3_shopkeeper");

	_vTiles.clear();

	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		delete(*iter);
	}
}

void Stage1_2Scene::update(void)
{
	GameScene::update();

	if (PLAYER->getIsNextStage())
	{
		_vTerrainTile[_stairTileIdx]->_frameY = 0;
	}

	// 바닥 타일 타입이 계단일 시 씬 변경
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if ((_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::OPEN_STAIR && PLAYER->getIsNextStage()) || _padeAlpha == 255)
	{
		SCENEMANAGER->changeScene("boss");
	}
}

void Stage1_2Scene::render(void)
{
	GameScene::render();
}
