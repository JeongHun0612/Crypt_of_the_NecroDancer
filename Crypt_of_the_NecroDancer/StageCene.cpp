#include "Stdafx.h"
#include "GameScene.h"
#include "FileManager.h"

HRESULT GameScene::init(void)
{
	// ��Ʈ �ʱ�ȭ
	BEAT->init();

	// Ÿ�� �ʱ�ȭ
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	// �÷��̾� ��ġ �ʱ�ȭ
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);
	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());
	PLAYER->setCurDirection(PLAYER_DIRECTION::NONE);
	PLAYER->setNextDirection(PLAYER->getCurDirection());

	// �ֳʹ� �ʱ�ȭ
	_vEnemy = ENEMYMANAGER->getEnemyList();

	// �Ű� ���� �ʱ�ȭ
	_isMove = false;

	// ���� �÷���
	SOUNDMANAGER->play("stage1-1", 0.5f);

	return S_OK;
}

void GameScene::release(void)
{
	SOUNDMANAGER->stop("stage1-1");
}

void GameScene::update(void)
{
	CAMERA->update();
	PLAYER->update();
	BEAT->update();

	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->update();
	}

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

	int _curIdx = MAX_STAGE1_COL * PLAYER->getPosIdxY() + PLAYER->getPosIdxX();
	int _nextIdx = MAX_STAGE1_COL * PLAYER->getNextIdxY() + PLAYER->getNextIdxX();

	int _leftIdx = _curIdx - 1;
	int _rightIdx = _curIdx + 1;
	int _topIdx = _curIdx - MAX_STAGE1_COL;
	int _bottomIdx = _curIdx + MAX_STAGE1_COL;


	// �Ʒ� �ʿ� Ÿ���� ���� �� �׸��� �����
	if (_vWallTile[_bottomIdx]->_idxX == PLAYER->getPosIdxX() && _vWallTile[_bottomIdx]->_idxY == PLAYER->getPosIdxY() + 1 && _vWallTile[_bottomIdx]->_isCollider)
	{
		PLAYER->setShadowAlpha(0);
	}

	// Ű �Է��� ���� �� (�� / �� / �� / ��)
	if (PLAYER->getNextDirection() != PLAYER_DIRECTION::NONE)
	{
		if (BEAT->getBeat())
		{
			_isMove = true;
			BEAT->setIsSuccess(true);
			PLAYER->setCurDirection(PLAYER->getNextDirection());

			// �ٴ� Ÿ�� �˻�
			if (_vTerrainTile[_nextIdx]->_terrain == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}

			// �浹ü �߰� ��
			if (TILEMAP->getStage1Wall()[_nextIdx]->_isCollider)
			{
				_isMove = false;
				PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());

				// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
				if (_vWallTile[_nextIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
				{
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// �� �μ���
					_vWallTile[_nextIdx]->_isExist = false;
					_vWallTile[_nextIdx]->_isCollider = false;
					CAMERA->setShakeCount(15);
					SOUNDMANAGER->play("dig" + to_string(RND->getFromIntTo(1, 6)));

					switch (_vWallTile[_nextIdx]->_wall)
					{
					case WALL::DIRT:
						SOUNDMANAGER->play("dig_dirt");
						break;
					case WALL::BRICK:
						SOUNDMANAGER->play("dig_brick");
						break;
					case WALL::STONE:
						SOUNDMANAGER->play("dig_stone");
						break;
					}
				}
			}

			// �ֳʹ� �˻�
			for (auto iter = _vEnemy.begin(); iter != _vEnemy.end();)
			{
				if ((*iter)->getIdxX() == PLAYER->getNextIdxX() && (*iter)->getIdxY() == PLAYER->getNextIdxY())
				{
					_isMove = false;
					CAMERA->setShakeCount(15);
					PLAYER->getCurWeapon()->setIsAttack(true);
					SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));

					(*iter)->setCurHP((*iter)->getCurHP() - PLAYER->getCurWeapon()->getPower());
					//SOUNDMANAGER->play("cauldron_hit");

					if ((*iter)->getCurHP() <= 0)
					{
						// ���� ��ü ���� �� ���� ����
						(*iter)->release();
						delete(*iter);
						iter = _vEnemy.erase(iter);
					}
					else
					{
						++iter;
					}
				}
				else
				{
					++iter;
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
		}
		else
		{
			BEAT->setIsMissed(true);
			PLAYER->setNextIdxX(PLAYER->getPosIdxX());
			PLAYER->setNextIdxY(PLAYER->getPosIdxY());
		}

		PLAYER->setNextDirection(PLAYER_DIRECTION::NONE);
	}
}

void GameScene::render(void)
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// ���� ���
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// ����� ���
	if (KEYMANAGER->isToggleKey(VK_F1) && !_vTerrainTile.empty())
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2) && !_vTerrainTile.empty())
	{
		showTileDist(_vTerrainTile);
	}

	// ��Ʈ ���
	BEAT->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());
}

HRESULT GameScene::tileSet(vector<Tile*>& _vTile, TILE_TYPE type)
{
	if (_vTile.empty()) return E_FAIL;

	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_STAGE1_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_STAGE1_ROW - 1) continue;

			int vIndex = (curIdxY * MAX_STAGE1_COL) + curIdxX;

			// Ÿ���� �׸��� �ʰڴٸ� continue
			if (!_vTile[vIndex]->_isExist) continue;

			// �÷��̾�� Ÿ�ϰ��� �Ÿ�
			int distance = sqrt(pow(_vTile[vIndex]->_idxX - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex]->_idxY - PLAYER->getPosIdxY(), 2));

			// �÷��̾�� Ÿ�ϰ��� �Ÿ��� ���� ���İ�
			int _alpha = getAlphaSet(distance, PLAYER->getLightPower());

			if (distance < PLAYER->getLightPower() || _vTile[vIndex]->_isLight)
			{
				switch (type)
				{
				case TILE_TYPE::TERRAIN:
					IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
						_vTile[vIndex]->_frameX,
						_vTile[vIndex]->_frameY,
						_alpha);
					break;
				case TILE_TYPE::WALL:
					IMAGEMANAGER->findImage("wall1")->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE) - 32,
						_vTile[vIndex]->_frameX,
						_vTile[vIndex]->_frameY,
						_alpha);
					break;
				case TILE_TYPE::DECO:
					break;
				}

				if (!_vTile[vIndex]->_isLight)
				{
					_vTile[vIndex]->_isLight = true;
				}
			}
		}
	}
}

void GameScene::enemySet()
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_STAGE1_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_STAGE1_ROW - 1) continue;
		}
	}
}

int GameScene::getAlphaSet(int distance, int rightPower)
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

void GameScene::showTileNum(vector<Tile*> _vTile)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_STAGE1_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_STAGE1_ROW - 1) continue;

			int vIndex = curIdxY * MAX_STAGE1_COL + curIdxX;

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _vTile[vIndex]->_idxY, _vTile[vIndex]->_idxX);

			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strIdx, strlen(strIdx));
		}
	}
}

void GameScene::showTileDist(vector<Tile*> _vTile)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_STAGE1_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_STAGE1_ROW - 1) continue;

			int vIndex = curIdxY * MAX_STAGE1_COL + curIdxX;

			int distance = sqrt(pow(_vTile[vIndex]->_idxX - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex]->_idxY - PLAYER->getPosIdxY(), 2));

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strDist, strlen(strDist));
		}
	}
}
