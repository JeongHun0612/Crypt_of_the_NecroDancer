#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	// Ÿ�� �ʱ�ȭ
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(5, 5);

	// UI �ʱ�ȭ
	UIMANAGER->init();

	// �ֳʹ� �ʱ�ȭ
	ENEMYMANAGER->init();

	// ���� �÷���
	SOUNDMANAGER->play("lobby", 0.5f);

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
	if (!PLAYER->getIsMove())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && !_isMove)
		{
			PLAYER->setNextIdxX(PLAYER->getPosIdxX() - 1);
			PLAYER->setNextDirection(PLAYER_DIRECTION::LEFT);
			_isMove = true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && !_isMove)
		{
			PLAYER->setNextIdxX(PLAYER->getPosIdxX() + 1);
			PLAYER->setNextDirection(PLAYER_DIRECTION::RIGHT);
			_isMove = true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_isMove)
		{
			PLAYER->setNextIdxY(PLAYER->getPosIdxY() - 1);
			PLAYER->setNextDirection(PLAYER_DIRECTION::UP);
			_isMove = true;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && !_isMove)
		{
			PLAYER->setNextIdxY(PLAYER->getPosIdxY() + 1);
			PLAYER->setNextDirection(PLAYER_DIRECTION::DOWN);
			_isMove = true;
		}
	}

	// �Ʒ� �ʿ� Ÿ���� ���� �� �׸��� �����
	for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
	{
		if (iter->getIdxX() == PLAYER->getPosIdxX() && (iter->getIdxY() == PLAYER->getNextIdxY() + 1 || iter->getIdxY() == PLAYER->getPosIdxY() + 1) && iter->getIsExist())
		{
			PLAYER->setShadowAlpha(0);
			break;
		}
	}

	// Ű �Է��� ���� �� (�� / �� / �� / ��)
	if (PLAYER->getNextDirection() != PLAYER_DIRECTION::NONE)
	{
		PLAYER->setShadowAlpha(130);
		PLAYER->setCurDirection(PLAYER->getNextDirection());

		// �ٴ� Ÿ�� �˻�
		for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
		{
			// ���� �������� �̵�
			if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getTerrain() == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}
		}

		// �� Ÿ�� �˻�
		for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
		{
			// �Ʒ� �ʿ� Ÿ���� ���� �� �׸��� �����
			if (iter->getIdxX() == PLAYER->getPosIdxX() && (iter->getIdxY() == PLAYER->getNextIdxY() + 1 || iter->getIdxY() == PLAYER->getPosIdxY() + 1) && iter->getIsExist())
			{
				PLAYER->setShadowAlpha(0);
			}

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
				}
			}
		}
		
		if (_isMove)
		{
			PLAYER->setIsMove(true);
			CAMERA->setMaxCol(MAX_LOBBY_COL);
		}
		else
		{
			// �÷��̾� ��ġ ��ǥ ����
			PLAYER->setNextIdxX(PLAYER->getPosIdxX());
			PLAYER->setNextIdxY(PLAYER->getPosIdxY());
		}

		PLAYER->setNextDirection(PLAYER_DIRECTION::NONE);
		_isMove = false;
	}
}

void LobbyScene::render()
{
	// �ٴ� Ÿ�� ���
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
				IMAGEMANAGER->findImage("terrain1")->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_vTile[vIndex].getFrameX(),
					_vTile[vIndex].getFrameY());
				break;
			case TILE_TYPE::WALL:
				IMAGEMANAGER->findImage("wall1")->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE) - 32,
					_vTile[vIndex].getFrameX(),
					_vTile[vIndex].getFrameY());
				break;
			case TILE_TYPE::DECO:
				break;
			}
		}
	}
}