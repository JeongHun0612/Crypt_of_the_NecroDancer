#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "Stage1_1Scene.h"

HRESULT Stage1_1Scene::init(void)
{
	GameScene::init();

	// Ÿ�� �ʱ�ȭ
	FileManager::loadTileMapFile("Stage1_1_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1_1_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	_vTiles.push_back(_vTerrainTile);
	_vTiles.push_back(_vWallTile);

	_tileMaxCol = MAX_STAGE1_1_COL;
	_tileMaxRow = MAX_STAGE1_1_ROW;

	// �ֳʹ� �ʱ�ȭ
	FileManager::loadEnemyFile("Stage1_1_Enemy.txt", _vEnemy, _vTiles, _tileMaxCol);

	// ������ �ʱ�ȭ
	FileManager::loadItemFile("Stage1_1_Item.txt", _vItem, _tileMaxCol);

	// ���� �������� ���
	_stairTileIdx = 22 * _tileMaxCol + 4;

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(13, 10, _vEnemy, _vItem, _vTiles, _tileMaxCol);

	// ��Ʈ �ʱ�ȭ
	BEAT->init("stage1_1.txt", "stage1_1");

	// ���� ���
	SOUNDMANAGER->play("stage1_1");
	SOUNDMANAGER->play("stage1_1_shopkeeper");

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

	// �ٴ� Ÿ�� Ÿ���� ����� �� �� ����
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if ((_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::OPEN_STAIR && PLAYER->getIsNextStage()) || _padeAlpha == 255)
	{
		SCENEMANAGER->changeScene("stage1_2");
	}
}

void Stage1_1Scene::render(void)
{
	GameScene::render();
}
