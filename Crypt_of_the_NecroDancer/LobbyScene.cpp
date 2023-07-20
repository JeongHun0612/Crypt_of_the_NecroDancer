#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// Ÿ�� �ʱ�ȭ
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(5, 5);

	// UI �ʱ�ȭ
	UIMANAGER->init();

	_nextDirection = PLAYER->getCurDirection();

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

		for (int i = TILEMAP->getStartIdx(); i < TILEMAP->getStartIdx() + INSPRECTION_RANGE; i++)
		{
			// ���� �� �˻�
			if (i > _vTerrainTile.size() - 1)
			{
				break;
			}

			// ���� �������� �̵�
			if (_vTerrainTile[i].getIdxX() == PLAYER->getNextIdxX() && _vTerrainTile[i].getIdxY() == PLAYER->getNextIdxY() && _vTerrainTile[i].getTerrain() == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}

			// �浹ü �߰� ��
			if (_vWallTile[i].getIdxX() == PLAYER->getNextIdxX() && _vWallTile[i].getIdxY() == PLAYER->getNextIdxY() && _vWallTile[i].getIsCollider())
			{
				_isMove = false;

				// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
				if (_vWallTile[i].getHardNess() > PLAYER->getCurShovel()->getHardNess())
				{
					PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// �� �μ���
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


		// ������ �� ���� setStartIndex ����
		TILEMAP->setStartIdx(PLAYER->getPosIdxX(), PLAYER->getNextIdxY(), MAX_LOBBY_COL);
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

			if (curIdxX < 0 || curIdxX > MAX_LOBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_LOBBY_ROW - 1) continue;

			int vIndex = (curIdxY * MAX_LOBBY_COL) + curIdxX;

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