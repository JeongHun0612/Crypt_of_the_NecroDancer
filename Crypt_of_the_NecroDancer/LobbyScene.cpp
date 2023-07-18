#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// Ÿ�� �ʱ�ȭ
	FileManager::loadTileMapFile("Stage1-1_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1-1_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	for (int i = 0; i < _vTerrainTile.size(); i++)
	{
		_vTerrainTile[i].isLight = false;
		_vWallTile[i].isLight = false;
	}

	// �÷��̾� �ʱ�ȭ
	PLAYER->init();
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	_nextIdxY = PLAYER->getPosIdxY();
	_nextIdxX = PLAYER->getPosIdxX();
	_nextDirection = PLAYER->getCurDirection();

	// UI �ʱ�ȭ
	UIMANAGER->init();

	Slime* _slime = new Slime_Green;
	_slime->init(3, 3, 2);

	_enemyTile[3][3].idxY = 3;
	_enemyTile[3][3].idxX = 3;

	_vSlime.push_back(_slime);

	Slime* _slime2 = new Slime_Blue;
	_slime2->init(3, 5, 2);

	_enemyTile[3][5].idxY = 3;
	_enemyTile[3][5].idxX = 5;

	_vSlime.push_back(_slime2);

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

	// �÷��̾� Ű�Է� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_nextIdxX = PLAYER->getPosIdxX() - 1;
		_nextDirection = PLAYER_DIRECTION::LEFT;
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

	// ī�޶� ����ŷ
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		CAMERA->cameraShake(30);
	}

	// Ű �Է��� ���� �� (�� / �� / �� / ��)
	if (_nextDirection != PLAYER_DIRECTION::NONE)
	{
		_isMove = true;
		PLAYER->setCurDirection(_nextDirection);
		PLAYER->getCurShovel()->setIsDig(false);

		for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
		{
			// ���� �������� �̵�
			if (iter->idxX == _nextIdxX && iter->idxY == _nextIdxY && iter->terrain == TERRAIN::STAIR)
			{
				cout << "���� �������� �̵�" << endl;
			}
		}

		for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
		{
			// �浹ü �߰� ��
			if (iter->idxX == _nextIdxX && iter->idxY == _nextIdxY && iter->isColiider)
			{
				_isMove = false;

				// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
				if (iter->hardness > PLAYER->getCurShovel()->getHardNess())
				{
					PLAYER->getCurShovel()->setIsDig(true);
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// �� �μ���
					iter->isExist = false;
				}
			}
		}

		for (auto iter = _vSlime.begin(); iter != _vSlime.end(); ++iter)
		{
			if ((*iter)->getIdxX() == _nextIdxX && (*iter)->getIdxY() == _nextIdxY)
			{
				_isMove = false;

				PLAYER->getCurWeapon()->setIsAttack(true);
			}
		}

		if (_isMove)
		{
			PLAYER->setIsMove(true);

			PLAYER->setPosIdxX(_nextIdxX);
			PLAYER->setPosIdxY(_nextIdxY);
		}

		_nextIdxY = PLAYER->getPosIdxY();
		_nextIdxX = PLAYER->getPosIdxX();
		_nextDirection = PLAYER_DIRECTION::NONE;
	}

	for (auto iter = _vSlime.begin(); iter != _vSlime.end(); ++iter)
	{
		(*iter)->update();
	}
}

void LobbyScene::render()
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_vTerrainTile);
	}

	// ���� ���
	for (auto iter = _vSlime.begin(); iter != _vSlime.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());
}

void LobbyScene::tileSet(vector<Tile> _vTile, TILE_TYPE type)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = curIdxY * MAX_ROBBY_COL + curIdxX;

			// Ÿ���� �׸��� �ʰڴٸ� continue
			if (!_vTile[vIndex].isExist) continue;

			// �÷��̾�� Ÿ�ϰ��� �Ÿ�
			int distance = sqrt(pow(_vTile[vIndex].idxX - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex].idxY - PLAYER->getPosIdxY(), 2));

			// �÷��̾�� Ÿ�ϰ��� �Ÿ��� ���� ���İ�
			int _alpha = getAlphaSet(distance, PLAYER->getLightPower());

			if (distance < PLAYER->getLightPower() || _vTile[vIndex].isLight)
			{
				switch (type)
				{
				case TILE_TYPE::TERRAIN:
					_terrainImg->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
						_vTile[vIndex].frameX,
						_vTile[vIndex].frameY,
						_alpha);
					break;
				case TILE_TYPE::WALL:
					_wallImg->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
						_vTile[vIndex].frameX,
						_vTile[vIndex].frameY,
						_alpha);
					break;
				case TILE_TYPE::DECO:
					break;
				}

				_vTile[vIndex].isLight = true;
			}
		}
	}
}

void LobbyScene::enemySet()
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;
		}
	}
}

int LobbyScene::getAlphaSet(int distance, int rightPower)
{
	int minAlpha = 80;

	int alphaAmount = (255 - minAlpha) / rightPower;

	if (distance < rightPower)
	{
		return 255 - alphaAmount * distance;
	}
	else
	{
		return minAlpha;
	}
}

void LobbyScene::showTileNum(vector<Tile> _vTile)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = curIdxY * MAX_ROBBY_COL + curIdxX;

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _vTile[vIndex].idxY, _vTile[vIndex].idxX);

			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strIdx, strlen(strIdx));
		}
	}
}

void LobbyScene::showTileDist(vector<Tile> _vTile)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = curIdxY * MAX_ROBBY_COL + curIdxX;

			int distance = sqrt(pow(_vTile[vIndex].idxX - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex].idxY - PLAYER->getPosIdxY(), 2));

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strDist, strlen(strDist));
		}
	}
}
