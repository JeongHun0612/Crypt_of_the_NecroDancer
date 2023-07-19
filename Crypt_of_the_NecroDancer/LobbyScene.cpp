#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// Ÿ�� �ʱ�ȭ
	FileManager::loadTileMapFile("Lobby_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Lobby_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	cout << _vTerrainTile.size() << endl;

	// �÷��̾� �ʱ�ȭ
	PLAYER->init();
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());

	_nextDirection = PLAYER->getCurDirection();

	// UI �ʱ�ȭ
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

	// �÷��̾� Ű�Է� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		PLAYER->setNextIdxX(PLAYER->getPosIdxX() - 1);
		_nextDirection = PLAYER_DIRECTION::LEFT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		PLAYER->setNextIdxX(PLAYER->getPosIdxX() + 1);
		_nextDirection = PLAYER_DIRECTION::RIGHT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		PLAYER->setNextIdxY(PLAYER->getPosIdxY() - 1);
		_nextDirection = PLAYER_DIRECTION::UP;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		PLAYER->setNextIdxY(PLAYER->getPosIdxY() + 1);
		_nextDirection = PLAYER_DIRECTION::DOWN;
	}

	// Ű �Է��� ���� �� (�� / �� / �� / ��)
	if (_nextDirection != PLAYER_DIRECTION::NONE)
	{
		_isMove = true;
		PLAYER->setCurDirection(_nextDirection);

		for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
		{
			// ���� �������� �̵�
			if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getTerrain() == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}
		}

		for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
		{
			// �浹ü �߰� ��
			if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getIsCollider())
			{
				_isMove = false;

				// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
				if (iter->getHardNess() > PLAYER->getCurShovel()->getHardNess())
				{
					PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// �� �μ���
					iter->setIsExist(false);
				}
			}
		}

		if (_isMove)
		{
			PLAYER->setIsMove(true);
			PLAYER->setPosIdxX(PLAYER->getNextIdxX());
			PLAYER->setPosIdxY(PLAYER->getNextIdxY());
		}

		PLAYER->setNextIdxX(PLAYER->getPosIdxX());
		PLAYER->setNextIdxY(PLAYER->getPosIdxY());
		_nextDirection = PLAYER_DIRECTION::NONE;
	}
}

void LobbyScene::render()
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());
}

HRESULT LobbyScene::tileSet(vector<Tile>& _vTile, TILE_TYPE type)
{
	if (_vTile.empty()) return E_FAIL;


	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = (curIdxY * MAX_ROBBY_COL) + curIdxX;

			// Ÿ���� �׸��� �ʰڴٸ� continue
			if (!_vTile[vIndex].getIsExist()) continue;

			switch (type)
			{
			case TILE_TYPE::TERRAIN:
				_terrainImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_vTile[vIndex].getFrameX(),
					_vTile[vIndex].getFrameY());
				break;
			case TILE_TYPE::WALL:
				_wallImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_vTile[vIndex].getFrameX(),
					_vTile[vIndex].getFrameY());
				break;
			case TILE_TYPE::DECO:
				break;
			}
		}
	}
}