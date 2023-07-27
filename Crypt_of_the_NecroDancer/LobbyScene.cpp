#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// Ÿ�� �ʱ�ȭ
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	for (int i = 0; i < _vTerrainTile.size(); i++)
	{
		_vTerrainTile[i]->_isLight = true;
		_vTerrainTile[i]->_alpha = 255;

		_vWallTile[i]->_isLight = true;
		_vWallTile[i]->_alpha = 255;
	}

	_tileMaxCol = MAX_LOBBY_COL;
	_tileMaxRow = MAX_LOBBY_ROW;

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(6, 3);
	
	// �ֳʹ� �ʱ�ȭ
	ENEMYMANAGER->init();

	// ��Ʈ �ʱ�ȭ
	BEAT->setIsBeat(true);

	// UI �ʱ�ȭ
	UIMANAGER->init();

	// ���� �÷���
	SOUNDMANAGER->play("lobby", 0.5f);

	return S_OK;
}

void LobbyScene::release()
{
	SOUNDMANAGER->stop("lobby");
}

void LobbyScene::update()
{
	CAMERA->update();

	PLAYER->update();

	// �ٴ� Ÿ�� Ÿ���� ����� �� �� ����
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTiles[(int)TILE_TYPE::TERRAIN][_nextTileIdx]->_terrainType == TERRAIN_TYPE::STAIR)
	{
		SCENEMANAGER->changeScene("stage1_1");
	}
}

void LobbyScene::render()
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());

	// ����� ���
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_vTerrainTile);
	}
}