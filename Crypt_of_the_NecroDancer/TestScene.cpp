#include "Stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init(void)
{
	_pos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };
	_posIdx = { 5, 5 };
	_player = RectMakeCenter(WINSIZE_X_HALF, WINSIZE_Y_HALF, 64, 64);

	_terrainImg = IMAGEMANAGER->findImage("tile_terrain");
	_wallImg = IMAGEMANAGER->findImage("tile_wall");

	// Terrain 데이터
	static bool test = true;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			_tileTerrain[i][j].posIdx = { i, j };
			_tileTerrain[i][j].isColiider = false;

			if (test)
			{
				if (j % 2 == 0)
				{
					_tileTerrain[i][j].imgNum = { 0, 0 };
				}
				else
				{
					_tileTerrain[i][j].imgNum = { 64, 0 };
				}
			}
			else
			{
				if (j % 2 == 0)
				{
					_tileTerrain[i][j].imgNum = { 64, 0 };
				}
				else
				{
					_tileTerrain[i][j].imgNum = { 0, 0 };
				}
			}
		}

		test = !test;
	}

	// wall 데이터
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			_tileWall[i][j].posIdx = { i, j };

			if (i == 0 || i == 29 || j == 0 || j == 29)
			{
				_tileWall[i][j].imgNum = { 0, 738 };
				_tileWall[i][j].isColiider = true;
			}
			else
			{
				_tileWall[i][j].imgNum = { 0, 0 };
				_tileWall[i][j].isColiider = false;
			}
		}
	}

	//  testTile 데이터
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_tileTest[i][j].posIdx = { i, j };

			if (i == 0 || i == 7 || j == 0 || j == 7)
			{
				_tileTest[i][j].isColiider = true;
				_tileTest[i][j].imgNum = { 64, 64 };
			}
			else
			{
				_tileTest[i][j].isColiider = false;
				_tileTest[i][j].imgNum = { 0, 0 };
			}
		}
	}

	return S_OK;
}

void TestScene::release(void)
{
}

void TestScene::update(void)
{
	//CAMERA->setTargetPos(_pos.x, _pos.y);

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (!_tileTest[_posIdx.y][_posIdx.x - 1].isColiider)
		{
			_pos.x -= 64.f;
			_posIdx.x--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (!_tileTest[_posIdx.y][_posIdx.x + 1].isColiider)
		{
			_pos.x += 64.f;
			_posIdx.x++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (!_tileTest[_posIdx.y - 1][_posIdx.x].isColiider)
		{
			_pos.y -= 64.f;
			_posIdx.y--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (!_tileTest[_posIdx.y + 1][_posIdx.x].isColiider)
		{
			_pos.y += 64.f;
			_posIdx.y++;
		}
	}
}

void TestScene::render(void)
{
	for (int i = -7; i < 7; i++)
	{
		for (int j = -11; j < 11; j++)
		{
			if (_posIdx.x + j < 0 || _posIdx.y + i < 0) continue;

			// 29 == tile max count
			if (_posIdx.x + j > 7 || _posIdx.y + i > 7) continue;

			//RectangleMakeCenter(getMemDC(), WINSIZE_X_HALF + (j * 64), WINSIZE_Y_HALF + (i * 64), 64, 64);

			_terrainImg->render(
				getMemDC(),
				WINSIZE_X_HALF + (j * 64) - 32,
				WINSIZE_Y_HALF + (i * 64) - 32,
				_tileTest[_posIdx.y + i][_posIdx.x + j].imgNum.x,
				_tileTest[_posIdx.y + i][_posIdx.x + j].imgNum.y,
				64, 64
			);

			//_terrainImg->render(
			//	getMemDC(),
			//	WINSIZE_X_HALF + (j * 64) - 32,
			//	WINSIZE_Y_HALF + (i * 64) - 32,
			//	_tileTerrain[_posIdx.y + i][_posIdx.x + j].imgNum.x,
			//	_tileTerrain[_posIdx.y + i][_posIdx.x + j].imgNum.y,
			//	64, 64
			//);

			//_wallImg->render(
			//	getMemDC(),
			//	WINSIZE_X_HALF + (j * 64) - 32,
			//	WINSIZE_Y_HALF + (i * 64) - 32,
			//	_tileWall[_posIdx.y + i][_posIdx.x + j].imgNum.x,
			//	_tileWall[_posIdx.y + i][_posIdx.x + j].imgNum.y,
			//	64, 64
			//);


			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _posIdx.x + j, _posIdx.y + i);

			TextOut(getMemDC(), (WINSIZE_X_HALF - 32) + (j * 64), (WINSIZE_Y_HALF - 32) + (i * 64), strIdx, strlen(strIdx));
		}
	}

	char idx[128];
	sprintf_s(idx, "[%d, %d]", _posIdx.x, _posIdx.y);
	TextOut(getMemDC(), WINSIZE_X - 50, 0, idx, strlen(idx));

	RectangleMakeCenter(getMemDC(), _pos.x, _pos.y, 64, 64);
}
