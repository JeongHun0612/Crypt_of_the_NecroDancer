#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	
	FileManager::loadTileMapFile("Stage1-1_Terrain.txt", _vTerrainTile);
	
	for (int i = 0; i < _vTerrainTile.size(); i++)
	{
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].idxX = _vTerrainTile[i].idxX;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].idxY = _vTerrainTile[i].idxY;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].frameX = _vTerrainTile[i].frameX;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].frameY = _vTerrainTile[i].frameY;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].isColiider = _vTerrainTile[i].isColiider;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].isExist = _vTerrainTile[i].isExist;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].hardness = _vTerrainTile[i].hardness;
		_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].terrain = TERRAIN::GROUND;
	}

	_terrainTile[7][3].terrain = TERRAIN::STAIR;
	_terrainTile[7][7].terrain = TERRAIN::STAIR;
	

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
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	_nextIdxY = PLAYER->getPosIdxY();
	_nextIdxX = PLAYER->getPosIdxX();
	_nextDirection = PLAYER->getCurDirection();

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
		_nextIdxX = PLAYER->getPosIdxX() - 1;
		_nextDirection = PLAYER_DIRECTION::LEFT;

		//if (_wallTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x - 1].hardness < PLAYER->getShovel().hardness)
		//{
		//	_wallTile[PLAYER->getPosIdx().y][PLAYER->getPosIdx().x - 1].isExist = false;
		//}
		//else
		//{
		//	cout << "안부셔짐" << endl;
		//}

		//char str[100];
		//sprintf_s(str, "dig%d", RND->getFromIntTo(1, 5));
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_nextIdxX = PLAYER->getPosIdxX() + 1;
		_nextDirection = PLAYER_DIRECTION::RIGHT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_nextIdxY = PLAYER->getPosIdxY() - 1;
		_nextDirection = PLAYER_DIRECTION::UP;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_nextIdxY = PLAYER->getPosIdxY() + 1;
		_nextDirection = PLAYER_DIRECTION::DOWN;
	}

	// 카메라 쉐이킹
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		CAMERA->cameraShake(30);
	}

	// 키 입력이 있을 시 (좌 / 우 / 상 / 하)
	if (_nextDirection != PLAYER_DIRECTION::NONE)
	{
		PLAYER->setCurDirection(_nextDirection);
		PLAYER->getCurShovel()->setIsDig(false);

		// 충돌체 발견 시
		if (_wallTile[_nextIdxY][_nextIdxX].isColiider)
		{
			// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
			if (_wallTile[_nextIdxY][_nextIdxX].hardness > PLAYER->getCurShovel()->getHardNess())
			{
				PLAYER->getCurShovel()->setIsDig(true);
				SOUNDMANAGER->play("dig_fail");
			}
			else
			{
				// 벽 부수기
			}

			_nextIdxY = PLAYER->getPosIdxY();
			_nextIdxX = PLAYER->getPosIdxX();
		}
		else
		{
			PLAYER->setIsMove(true);

			PLAYER->setPosIdxX(_nextIdxX);
			PLAYER->setPosIdxY(_nextIdxY);
		}

		// 다음 스테이지 이동
		if (_terrainTile[_nextIdxY][_nextIdxX].terrain == STAIR)
		{
			cout << "다음 스테이지 이동" << endl;
		}

		_nextDirection = PLAYER_DIRECTION::NONE;
	}
}

void LobbyScene::render()
{
	// 타일 출력
	tileSet(_terrainTile, TILE_TYPE::TERRAIN);
	tileSet(_wallTile, TILE_TYPE::WALL);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_terrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_terrainTile);
	}

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
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			if (!_tile[curIdxY][curIdxX].isExist) continue;

			int distance = sqrt(pow(_tile[curIdxY][curIdxX].idxX - PLAYER->getPosIdxX(), 2) + pow(_tile[curIdxY][curIdxX].idxY - PLAYER->getPosIdxY(), 2));

			int _alpha = 155;

			if (distance < PLAYER->getRightDist())
			{
				_alpha = 255 - distance * (100 / PLAYER->getRightDist());
			}

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

void LobbyScene::showTileNum(Tile _tile[][MAX_ROBBY_COL])
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _tile[curIdxY][curIdxX].idxY, _tile[curIdxY][curIdxX].idxX);

			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strIdx, strlen(strIdx));
		}
	}
}

void LobbyScene::showTileDist(Tile _tile[][MAX_ROBBY_COL])
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int distance = sqrt(pow(_tile[curIdxY][curIdxX].idxX - PLAYER->getPosIdxX(), 2) + pow(_tile[curIdxY][curIdxX].idxY - PLAYER->getPosIdxY(), 2));

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strDist, strlen(strDist));
		}
	}
}
