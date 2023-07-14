#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	FileManager::loadTileFile("Stage1-1_Ground.txt", _vTerrainTile);

	SOUNDMANAGER->play("stage1-1");

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// terrain
	for (int i = 0; i < MAX_ROBBY_ROW; i++)
	{
		for (int j = 0; j < MAX_ROBBY_COL; j++)
		{
			_terrainTile[i][j].posIdx = { i, j };
			_terrainTile[i][j].isExist = true;
			_terrainTile[i][j].isColiider = false;

			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
					_terrainTile[i][j].imgNum = { 0, 0 };
				}
				else
				{
					_terrainTile[i][j].imgNum = { 1, 0 };
				}
			}
			else
			{
				if (j % 2 == 0)
				{
					_terrainTile[i][j].imgNum = { 1, 0 };
				}
				else
				{
					_terrainTile[i][j].imgNum = { 0, 0 };
				}
			}
		}
	}

	// wall
	for (int i = 0; i < MAX_ROBBY_ROW; i++)
	{
		for (int j = 0; j < MAX_ROBBY_COL; j++)
		{
			_wallTile[i][j].posIdx = { i, j };

			if (i == 0 || i == MAX_ROBBY_ROW - 1 || j == 0 || j == MAX_ROBBY_COL - 1)
			{
				_wallTile[i][j].imgNum = { 0, 6 };
				_wallTile[i][j].isColiider = true;
				_wallTile[i][j].isExist = true;
			}
			else
			{
				_wallTile[i][j].imgNum = { 0, 0 };
				_wallTile[i][j].isColiider = false;
				_wallTile[i][j].isExist = false;
			}
		}
	}

	// �÷��̾� �ʱ�ȭ
	_player.init();
	_player.setPosIdx(5, 5);

	return S_OK;
}

void LobbyScene::release()
{
	SOUNDMANAGER->stop("stage1-1");
}

void LobbyScene::update()
{
	_player.update();

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_wallTile[_player.getPosIdx().y][_player.getPosIdx().x - 1].isColiider)
		{
			cout << "��! ��!" << endl;
		}
		else
		{
			_player.setIsMove(true);
			_player.setDirection(PLAYER_DIRECTION::LEFT);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_wallTile[_player.getPosIdx().y][_player.getPosIdx().x + 1].isColiider)
		{
			cout << "��! ��!" << endl;
		}
		else
		{
			_player.setIsMove(true);
			_player.setDirection(PLAYER_DIRECTION::RIGHT);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_wallTile[_player.getPosIdx().y - 1][_player.getPosIdx().x].isColiider)
		{
			cout << "��! ��!" << endl;
		}
		else
		{
			_player.setIsMove(true);
			_player.setDirection(PLAYER_DIRECTION::UP);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_wallTile[_player.getPosIdx().y + 1][_player.getPosIdx().x].isColiider)
		{
			cout << "��! ��!" << endl;
		}
		else
		{
			_player.setIsMove(true);
			_player.setDirection(PLAYER_DIRECTION::DOWN);
		}
	}
}

void LobbyScene::render()
{
	// Ÿ�� ���
	for (int i = -7; i < 7; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = _player.getPosIdx().x + j;
			int curIdxY = _player.getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			// terrain Ÿ�� ���
			if (_terrainTile[curIdxY][curIdxX].isExist)
			{
				_terrainImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_terrainTile[curIdxY][curIdxX].imgNum.x,
					_terrainTile[curIdxY][curIdxX].imgNum.y);
			}

			// wall Ÿ�� ���
			if (_wallTile[curIdxY][curIdxX].isExist)
			{
				_wallImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_wallTile[curIdxY][curIdxX].imgNum.x,
					_wallTile[curIdxY][curIdxX].imgNum.y);
			}

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", curIdxX, curIdxY);

			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strIdx, strlen(strIdx));
		}
	}

	// �÷��̾� ���
	_player.render(getMemDC());
}
