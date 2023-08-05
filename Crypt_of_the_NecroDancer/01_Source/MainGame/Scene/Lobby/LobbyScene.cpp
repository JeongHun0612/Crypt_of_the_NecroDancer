#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// Ÿ�� �ʱ�ȭ
	FileManager::loadTileMapFile("Lobby_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Lobby_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	_vTiles.push_back(_vTerrainTile);
	_vTiles.push_back(_vWallTile);

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
	PLAYER->init(6, 3, _vTiles);

	// ��Ʈ �ʱ�ȭ
	BEAT->init();
	BEAT->setIsBeat(true);

	// UI �ʱ�ȭ
	UIMANAGER->init();

	// ���� �÷���
	SOUNDMANAGER->play("lobby");

	return S_OK;
}

void LobbyScene::release()
{
	GameScene::release();

	SOUNDMANAGER->stop("lobby");
}

void LobbyScene::update()
{
	CAMERA->update();

	PLAYER->update();

	// �ٴ� Ÿ�� Ÿ���� ����� �� �� ����
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::OPEN_STAIR)
	{
		// ��������1 ����
		if (PLAYER->getPosIdx().x == 7 && PLAYER->getPosIdx().y == 5)
		{
			SCENEMANAGER->changeScene("boss");
		}
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