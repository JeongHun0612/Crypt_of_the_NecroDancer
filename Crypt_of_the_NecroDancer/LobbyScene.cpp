#include "Stdafx.h"
#include "LobbyScene.h"


HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("stage1-1");

	BEAT->init();

	_player.init();

	_tileImg = IMAGEMANAGER->findImage("tile_terrain");

	//for (int i = 0; i < MAX_TILE_ROW; i++)
	//{
	//	for (int j = 0; j < MAX_TILE_COL; j++)
	//	{
	//		_tile[i][j].posIdx = { i, j };
	//		_tile[i][j].size = { TILESIZE, TILESIZE };
	//		_tile[i][j].rc = RectMake(_tile[i][j].posIdx.x * 64, _tile[i][j].posIdx.y * 64, 64, 64);

	//		if (j % 2 == 0)
	//		{
	//			_tile[i][j].imgNum = { 0, 0 };
	//		}
	//		else
	//		{
	//			_tile[i][j].imgNum = { 64, 0 };
	//		}

	//		if (i == 0 || i == MAX_TILE_ROW - 1)
	//		{
	//			_tile[i][j].imgNum = { 64, 64 };
	//		}

	//		if (j == 0 || j == MAX_TILE_COL - 1)
	//		{
	//			_tile[i][j].imgNum = { 64, 64 };
	//		}
	//	}
	//}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_testTile[i][j].posIdx = { i, j };
			_testTile[i][j].size = { TILESIZE, TILESIZE };
			_testTile[i][j].imgNum = 0;
		}
	}

	return S_OK;
}


void LobbyScene::release()
{
	SOUNDMANAGER->stop("stage1-1");
}

void LobbyScene::update()
{
	BEAT->update();

	_player.update();
}

void LobbyScene::render()
{
	// 비트 출력
	BEAT->render(getMemDC());

	// 플레이어 출력
	_player.render(getMemDC());
}
