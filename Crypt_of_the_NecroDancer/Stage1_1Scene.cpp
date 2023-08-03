#include "Stdafx.h"
#include "Stage1_1Scene.h"
#include "FileManager.h"

HRESULT Stage1_1Scene::init(void)
{
	// 타일 초기화
	FileManager::loadTileMapFile("Stage1_1_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1_1_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	_vTiles.push_back(_vTerrainTile);
	_vTiles.push_back(_vWallTile);

	_tileMaxCol = MAX_STAGE1_1_COL;
	_tileMaxRow = MAX_STAGE1_1_ROW;

	// 애너미 초기화
	FileManager::loadEnemyFile("Stage1_1_Enemy.txt", _vEnemy, _vTiles, _tileMaxCol);

	// 아이템 초기화
	//FileManager::loadItemFile("Stage1_1_Enemy.txt", _vItem);
	Item* _item1 = new Armor;
	_item1->init(12, 9, ITEM_TYPE::ARMOR, 2, 25);
	_vItem.push_back(_item1);

	Item* _item2 = new Weapon;
	_item2->init(13, 9, ITEM_TYPE::WEAPON, 2, 35);
	_vItem.push_back(_item2);

	Item* _item3 = new Armor;
	_item3->init(14, 9, ITEM_TYPE::ARMOR, 4, 45);
	_vItem.push_back(_item3);

	// 다음 스테이지 계단
	_stairTileIdx = 22 * _tileMaxCol + 4;

	// 플레이어 초기화
	PLAYER->init(13, 10, _vEnemy, _vItem, _vTiles, _tileMaxCol);

	// 비트 초기화
	BEAT->init("stage1_1.txt", "stage1_1");

	// 사운드 출력
	SOUNDMANAGER->play("stage1_1", 0.5f);
	SOUNDMANAGER->play("stage1_1_shopkeeper", 0.5f);

	return S_OK;
}

void Stage1_1Scene::release(void)
{
	GameScene::release();

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
		SCENEMANAGER->changeScene("stage1_2");
	}
}

void Stage1_1Scene::render(void)
{
	GameScene::render();
}
