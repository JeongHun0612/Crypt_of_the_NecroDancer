#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	// 타일 초기화
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
	{
		(*iter)->_isLight = true;
	}
	for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
	{
		(*iter)->_isLight = true;
	}

	_tileMaxCol = MAX_LOBBY_COL;
	_tileMaxRow = MAX_LOBBY_ROW;

	// 플레이어 초기화
	PLAYER->init(6, 3);
	
	// 애너미 초기화
	ENEMYMANAGER->init();

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
	CAMERA->update();

	PLAYER->update();

	// 바닥 타일 타입이 계단일 시 씬 변경
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTiles[(int)TILE_TYPE::TERRAIN][_nextTileIdx]->_terrainType == TERRAIN_TYPE::STAIR)
	{
		SCENEMANAGER->changeScene("stage1_1");
	}
}

void LobbyScene::render()
{
	// 타일 출력
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// 플레이어 출력
	PLAYER->render(getMemDC());

	// UI 출력
	UIMANAGER->render(getMemDC());

	// 디버그 모드
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_vTerrainTile);
	}
}