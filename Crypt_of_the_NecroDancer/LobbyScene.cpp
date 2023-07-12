#include "Stdafx.h"
#include "LobbyScene.h"


HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("stage1-1");

	BEAT->init();

	_player.init();

	_terrainImg = IMAGEMANAGER->findImage("tile_terrain");


	for (int i = 0; i < MAX_TILE_ROW; i++)
	{
		for (int j = 0; j < MAX_TILE_COL; j++)
		{
			_tile[i][j].posIdx = { i, j };
			_tile[i][j].isColiider = false;

			if (i == 0 || i == MAX_TILE_COL - 1 || j == 0 || j == MAX_TILE_ROW - 1)
			{
				_tile[i][j].imgNum = { 64, 64 };
			}
			else
			{
				_tile[i][j].imgNum = { 0, 0 };
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
	CAMERA->update();

	_player.update();
}

void LobbyScene::render()
{
	// 카메라 출력
	//DrawRectMake(getMemDC(), CAMERA->getCameraRect());

	// 타일 출력
	for (int i = -7; i < 7; i++)
	{
		for (int j = -11; j < 11; j++)
		{
			POINT curIdx = _player.getPosIdx();

			if (curIdx.x + j < 0 || curIdx.y + i < 0) continue;

			// 29 == tile max count
			if (curIdx.x + j > MAX_TILE_COL - 1 || curIdx.y + i > MAX_TILE_ROW - 1) continue;

			_terrainImg->render(
				getMemDC(),
				WINSIZE_X_HALF + (j * 64) - 32,
				WINSIZE_Y_HALF + (i * 64) - 32,
				_tile[curIdx.y + i][curIdx.x + j].imgNum.x,
				_tile[curIdx.y + i][curIdx.x + j].imgNum.y,
				64, 64
			);

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", curIdx.x + j, curIdx.y + i);

			TextOut(getMemDC(), (WINSIZE_X_HALF - 32) + (j * 64), (WINSIZE_Y_HALF - 32) + (i * 64), strIdx, strlen(strIdx));
		}
	}

	// 비트 출력
	BEAT->render(getMemDC());

	// 플레이어 출력
	_player.render(getMemDC());
}
