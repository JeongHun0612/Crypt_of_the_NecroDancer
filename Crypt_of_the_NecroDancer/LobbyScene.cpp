#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby");

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// terrain
	for (int i = 0; i < MAX_ROBBY_ROW; i++)
	{
		for (int j = 0; j < MAX_ROBBY_COL; j++)
		{
			_terrainTile[i][j].idxX = j;
			_terrainTile[i][j].idxY = i;
			_terrainTile[i][j].isExist = true;
			_terrainTile[i][j].isColiider = false;
			_terrainTile[i][j].terrain = TERRAIN::GROUND;

			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
					_terrainTile[i][j].frameX = 0;
					_terrainTile[i][j].frameY = 0;
				}
				else
				{
					_terrainTile[i][j].frameX = 1;
					_terrainTile[i][j].frameY = 0;
				}
			}
			else
			{
				if (j % 2 == 0)
				{
					_terrainTile[i][j].frameX = 1;
					_terrainTile[i][j].frameY = 0;
				}
				else
				{
					_terrainTile[i][j].frameX = 0;
					_terrainTile[i][j].frameY = 0;
				}
			}
		}
	}

	_terrainTile[7][3].terrain = TERRAIN::STAIR;
	_terrainTile[7][7].terrain = TERRAIN::STAIR;
	_terrainTile[7][3].frameX = 2;
	_terrainTile[7][7].frameX = 2;
	_terrainTile[7][3].frameY = 0;
	_terrainTile[7][7].frameY = 0;

	// wall
	for (int i = 0; i < MAX_ROBBY_ROW; i++)
	{
		for (int j = 0; j < MAX_ROBBY_COL; j++)
		{
			_wallTile[i][j].idxX = j;
			_wallTile[i][j].idxY = i;

			if (i == 0 || i == MAX_ROBBY_ROW - 1 || j == 0 || j == MAX_ROBBY_COL - 1)
			{
				_wallTile[i][j].frameX = 0;
				_wallTile[i][j].frameY = 6;
				_wallTile[i][j].isColiider = true;
				_wallTile[i][j].isExist = true;
				_wallTile[i][j].hardness = 5;
			}
			else
			{
				_wallTile[i][j].frameX = 0;
				_wallTile[i][j].frameY = 0;
				_wallTile[i][j].isColiider = false;
				_wallTile[i][j].isExist = false;
			}
		}
	}

	// 플레이어 초기화
	PLAYER->init();
	PLAYER->setPosIdx(5, 5);

	// UI 초기화
	UIMANAGER->init();

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


	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_wallTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x - 1].isColiider)
		{
			PLAYER->setIsShovel(true);

			//if (_wallTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x - 1].hardness < PLAYER->getShovel().hardness)
			//{
			//	_wallTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x - 1].isExist = false;
			//}
			//else
			//{
			//	cout << "안부셔짐" << endl;
			//}
		}
		else
		{
			PLAYER->setIsMove(true);
			PLAYER->setDirection(PLAYER_DIRECTION::LEFT);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_wallTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x + 1].isColiider)
		{
			cout << "깡! 깡!" << endl;
		}
		else
		{
			PLAYER->setIsMove(true);
			PLAYER->setDirection(PLAYER_DIRECTION::RIGHT);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_wallTile[PLAYER->getPosIdx().y - 1][PLAYER->getPosIdx().x].isColiider)
		{
			cout << "깡! 깡!" << endl;
		}
		else
		{
			PLAYER->setIsMove(true);
			PLAYER->setDirection(PLAYER_DIRECTION::UP);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_wallTile[PLAYER->getPosIdx().y + 1][PLAYER->getPosIdx().x].isColiider)
		{
			cout << "깡! 깡!" << endl;
		}
		else
		{
			PLAYER->setIsMove(true);
			PLAYER->setDirection(PLAYER_DIRECTION::DOWN);
		}
	}

	if (_terrainTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x].terrain == STAIR)
	{
		cout << "다음 스테이지 이동" << endl;
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		CAMERA->cameraShake(30);
	}
}

void LobbyScene::render()
{
	// 타일 출력
	tileSet(_terrainTile, TILE_TYPE::TERRAIN);
	tileSet(_wallTile, TILE_TYPE::WALL);

	//for (int i = -7; i < 8; i++)
	//{
	//	for (int j = -11; j < 12; j++)
	//	{
	//		int curIdxX = PLAYER->getPosIdx().x + j;
	//		int curIdxY = PLAYER->getPosIdx().y + i;

	//		if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
	//		if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

	//		// terrain 타일 출력
	//		if (!_terrainTile[curIdxY][curIdxX].isExist) continue;

	//		_terrainImg->frameRender(getMemDC(),
	//			CAMERA->getPos().x + (j * TILESIZE),
	//			CAMERA->getPos().y + (i * TILESIZE),
	//			_terrainTile[curIdxY][curIdxX].frameX,
	//			_terrainTile[curIdxY][curIdxX].frameY);
	//	}
	//}

	//for (int i = -7; i < 8; i++)
	//{
	//	for (int j = -11; j < 12; j++)
	//	{
	//		int curIdxX = PLAYER->getPosIdx().x + j;
	//		int curIdxY = PLAYER->getPosIdx().y + i;

	//		if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
	//		if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

	//		// wall 타일 출력
	//		if (_wallTile[curIdxY][curIdxX].isExist)
	//		{
	//			_wallImg->frameRender(getMemDC(),
	//				CAMERA->getPos().x + (j * TILESIZE),
	//				CAMERA->getPos().y + (i * TILESIZE),
	//				_wallTile[curIdxY][curIdxX].frameX,
	//				_wallTile[curIdxY][curIdxX].frameY);
	//		}

	//		char strIdx[15];
	//		sprintf_s(strIdx, "[%d, %d]", curIdxX, curIdxY);

	//		TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strIdx, strlen(strIdx));
	//	}
	//}

	//// 벡터 출력
	//for (int i = -7; i < 8; i++)
	//{
	//	for (int j = -11; j < 12; j++)
	//	{
	//		for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
	//		{
	//			_time += TIMEMANAGER->getDeltaTime();

	//			if (iter->idxX == PLAYER->getPosIdx().x + j && iter->idxY == PLAYER->getPosIdx().y + i)
	//			{
	//				_terrainImg->frameRender(getMemDC(),
	//					WINSIZE_X_HALF - 32 + (j * 64),
	//					WINSIZE_Y_HALF - 32 + (i * 64),
	//					iter->frameX,
	//					iter->frameY);

	//				break;
	//			}
	//		}

	//		char strIdx[15];
	//		sprintf_s(strIdx, "[%d, %d]", PLAYER->getPosIdx().x + j, PLAYER->getPosIdx().y + i);
	//		TextOut(getMemDC(), WINSIZE_X_HALF - 32 + (j * 64), WINSIZE_Y_HALF - 32 + (i * 64), strIdx, strlen(strIdx));
	//	}
	//}
	//cout << _time << endl;
	//_time = 0.0f;


	// 플레이어 출력
	PLAYER->render(getMemDC());

	UIMANAGER->render(getMemDC());
}

void LobbyScene::tileSet(Tile _tile[][MAX_ROBBY_COL], TILE_TYPE type)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdx().x + j;
			int curIdxY = PLAYER->getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			if (!_tile[curIdxY][curIdxX].isExist) continue;

			switch (type)
			{
			case TILE_TYPE::TERRAIN:
				_terrainImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_tile[curIdxY][curIdxX].frameX,
					_tile[curIdxY][curIdxX].frameY);
				break;
			case TILE_TYPE::WALL:
				_wallImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_wallTile[curIdxY][curIdxX].frameX,
					_wallTile[curIdxY][curIdxX].frameY);
				break;
			}
		}
	}
}
