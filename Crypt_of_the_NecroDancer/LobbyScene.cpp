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

	_camera = RectMakeCenter(_player.getPos().x, _player.getPos().y, WINSIZE_X, WINSIZE_Y);

	cout << _camera.left << endl;
	cout << _camera.top << endl;

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
	//for (int i = 0; i < 14; i++)
	//{
	//	for (int j = 0; j < 21; j++)
	//	{
	//		if (_player.getPosIdx().y - 5 >= 0 && j - _player.getPosIdx().x - 6 >= 0)
	//		{
	//			_tileImg->render(getMemDC(), _tile[i][j].posIdx.x * 64, _tile[i][j].posIdx.y * 64, _tile[i][j].imgNum.x, _tile[i][j].imgNum.y, _tile[i][j].size.x, _tile[i][j].size.y);
	//		}
	//	}
	//}

	//for (int i = 0; i < MAX_TILE_ROW; i++)
	//{
	//	for (int j = 0; j < MAX_TILE_COL; j++)
	//	{
	//		_tileImg->render(getMemDC(), _tile[i][j].posIdx.x * 64, _tile[i][j].posIdx.y * 64, _tile[i][j].imgNum.x, _tile[i][j].imgNum.y, _tile[i][j].size.x, _tile[i][j].size.y);

	//		RECT rt;
	//		if (IntersectRect(&rt, &_camera, &_tile[i][j].rc))
	//		{
	//			printf("[%d, %d]", _tile[i][j].posIdx.x, _tile[i][j].posIdx.y);
	//		}
	//	}
	//}

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (_camera.left + (j * 64) >= 0 && _camera.top + (i * 64) >= 0)
			{
				_tileImg->render(getMemDC(), j * 64, i * 64, 0, 0, 64, 64);
			}
		}
	}


	// 비트 출력
	BEAT->render(getMemDC());
	
	// 플레이어 출력
	_player.render(getMemDC());
}
