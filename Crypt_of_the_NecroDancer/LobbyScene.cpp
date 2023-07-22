#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// Ÿ�� �ʱ�ȭ
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	_tileMaxCol = MAX_LOBBY_COL;
	_tileMaxRow = MAX_LOBBY_ROW;

	_isLobby = true;

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(5, 5, _vTiles, MAX_LOBBY_COL);

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
	GameScene::update();

	// �ٴ� Ÿ�� Ÿ���� ����� �� �� ����
	int _nextTileIdx = (_tileMaxCol * _nextPosIdx.y) + _nextPosIdx.x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::STAIR)
	{
		SCENEMANAGER->changeScene("game");
	}
}

void LobbyScene::render()
{
	GameScene::render();
}