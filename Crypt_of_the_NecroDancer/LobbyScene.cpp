#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	GameScene::init();

	_isMove = false;

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
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			PLAYER->setNextDirection(PLAYER_DIRECTION::LEFT);
			PLAYER->setNextIdxX(PLAYER->getNextIdxX() - 1);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			PLAYER->setNextDirection(PLAYER_DIRECTION::RIGHT);
			PLAYER->setNextIdxX(PLAYER->getNextIdxX() + 1);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			PLAYER->setNextDirection(PLAYER_DIRECTION::UP);
			PLAYER->setNextIdxY(PLAYER->getNextIdxY() - 1);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			PLAYER->setNextDirection(PLAYER_DIRECTION::DOWN);
			PLAYER->setNextIdxY(PLAYER->getNextIdxY() + 1);
		}
	}

	int _curIdx = MAX_LOBBY_COL * PLAYER->getPosIdxY() + PLAYER->getPosIdxX();
	int _nextIdx = MAX_LOBBY_COL * PLAYER->getNextIdxY() + PLAYER->getNextIdxX();

	int _leftIdx = _curIdx - 1;
	int _rightIdx = _curIdx + 1;
	int _topIdx = _curIdx - MAX_LOBBY_COL;
	int _bottomIdx = _curIdx + MAX_LOBBY_COL;


	// �Ʒ� �ʿ� Ÿ���� ���� �� �׸��� �����
	if (_vWallTile[_bottomIdx]->_idxX == PLAYER->getPosIdxX() && _vWallTile[_bottomIdx]->_idxY == PLAYER->getPosIdxY() + 1 && _vWallTile[_bottomIdx]->_isCollider)
	{
		PLAYER->setShadowAlpha(0);
	}

	// Ű �Է��� ���� �� (�� / �� / �� / ��)
	if (PLAYER->getNextDirection() != PLAYER_DIRECTION::NONE)
	{
		_isMove = true;
		PLAYER->setCurDirection(PLAYER->getNextDirection());

		// �ٴ� Ÿ�� �˻�
		if (_vTerrainTile[_nextIdx]->_terrain == TERRAIN::STAIR)
		{
			SCENEMANAGER->changeScene("game");
		}

		// �浹ü �߰� ��
		if (_vWallTile[_nextIdx]->_isCollider)
		{
			_isMove = false;

			// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
			if (_vWallTile[_nextIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
			{
				PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());
				SOUNDMANAGER->play("dig_fail");
			}
			else
			{
				// �� �μ���
			}
		}

		// �����̱�
		if (_isMove)
		{
			PLAYER->setIsMove(true);
		}
		else
		{
			// �÷��̾� Next��ǥ �ʱ�ȭ
			PLAYER->setNextIdxX(PLAYER->getPosIdxX());
			PLAYER->setNextIdxY(PLAYER->getPosIdxY());
		}

		PLAYER->setNextDirection(PLAYER_DIRECTION::NONE);
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

HRESULT LobbyScene::tileSet(vector<Tile*>& _vTile, TILE_TYPE type)
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
			if (!_vTile[vIndex]->_isExist) continue;

			switch (type)
			{
			case TILE_TYPE::TERRAIN:
				IMAGEMANAGER->findImage("terrain1")->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_vTile[vIndex]->_frameX,
					_vTile[vIndex]->_frameY);
				break;
			case TILE_TYPE::WALL:
				IMAGEMANAGER->findImage("wall1")->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE) - 32,
					_vTile[vIndex]->_frameX,
					_vTile[vIndex]->_frameY);
				break;
			case TILE_TYPE::DECO:
				break;
			}
		}
	}
}