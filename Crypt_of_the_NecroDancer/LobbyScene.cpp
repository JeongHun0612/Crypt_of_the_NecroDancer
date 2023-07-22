#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// 타일 초기화
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	_tileMaxCol = MAX_LOBBY_COL;
	_tileMaxRow = MAX_LOBBY_ROW;

	_isLobby = true;

	// 플레이어 초기화
	PLAYER->init(5, 5, _vTiles, MAX_LOBBY_COL);

	// 비트 초기화
	BEAT->setIsBeat(true);

	// UI 초기화
	UIMANAGER->init();

	// 사운드 플레이
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

	// 바닥 타일 타입이 계단일 시 씬 변경
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