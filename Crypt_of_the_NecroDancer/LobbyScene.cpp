#include "Stdafx.h"
#include "LobbyScene.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("stage1-1");

	BEAT->init();

	_player.init();

	_tileImg = IMAGEMANAGER->findImage("tile_terrain");

	for (int i = 0; i < MAX_TILE_ROW; i++)
	{
		for (int j = 0; j < MAX_TILE_COL; j++)
		{
			_tile[i][j].posIdx = { j, i };
			_tile[i][j].size = { TILESIZE, TILESIZE };
			_tile[i][j].rc = RectMake(_tile[i][j].posIdx.x * 64, _tile[i][j].posIdx.y * 64, 64, 64);

			if (j % 2 == 0)
			{
				_tile[i][j].imgNum = { 0, 0 };
			}
			else
			{
				_tile[i][j].imgNum = { 64, 0 };
			}

			if (i == 0 || i == MAX_TILE_ROW - 1)
			{
				_tile[i][j].imgNum = { 64, 64 };
			}

			if (j == 0 || j == MAX_TILE_COL - 1)
			{
				_tile[i][j].imgNum = { 64, 64 };
			}
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
	//for (int i = 0; i < MAX_TILE_ROW; i++)
	//{
	//	for (int j = 0; j < MAX_TILE_COL; j++)
	//	{
	//		_tileImg->render(getMemDC(), j * 64 - CAMERA->getLookPos().x, i * 64 - CAMERA->getLookPos().y, _tile[i][j].imgNum.x, _tile[i][j].imgNum.y, TILESIZE, TILESIZE);
	//	}
	//}

	for (int i = CAMERA->getLookPosIdx().y - 8; i < CAMERA->getLookPosIdx().y + 8; i++, tileCountY++)
	{
		for (int j = CAMERA->getLookPosIdx().x - 11; j < CAMERA->getLookPosIdx().x + 11; j++, tileCountX++)
		{
			if (j < 0 || i < 0) continue;

			if (j >= MAX_TILE_COL || i >= MAX_TILE_ROW) continue;

			_tileImg->render(getMemDC(),
				tileCountX * 64 - CAMERA->getLookPos().x,
				tileCountY * 64 - CAMERA->getLookPos().y,
				_tile[j][i].imgNum.x, 
				_tile[j][i].imgNum.y, TILESIZE, TILESIZE);

			if (j == CAMERA->getLookPosIdx().x + 11 - 1)
			{
				tileCountX = 0;
			}
 		}

		if (i == CAMERA->getLookPosIdx().y + 8 - 1)
		{
			tileCountY = 0;
		}
	}

	// 비트 출력
	BEAT->render(getMemDC());

	// 플레이어 출력
	_player.render(getMemDC());
}
