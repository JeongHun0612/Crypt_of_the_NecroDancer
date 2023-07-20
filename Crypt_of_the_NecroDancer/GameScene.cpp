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
		if (BEAT->getBeat())
		{
			BEAT->setIsSuccess(true);
			PLAYER->setCurDirection(PLAYER->getNextDirection());

			// �ٴ� Ÿ�� �˻�
			for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
			{
				// ���� �������� �̵�
				if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getTerrain() == TERRAIN::STAIR)
				{
					cout << "���� �������� �̵�" << endl;
				}
			}

			// �� Ÿ�� �˻�
			for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
			{
				// �浹ü �߰� ��
				if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getIsCollider())
				{
					_isMove = false;
					PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());

					// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
					if (iter->getHardNess() > PLAYER->getCurShovel()->getHardNess())
					{
						SOUNDMANAGER->play("dig_fail");
					}
					else
					{
						// �� �μ���
						iter->setIsExist(false);
						iter->setIsCollider(false);
						CAMERA->setShakeCount(15);
						SOUNDMANAGER->play("dig" + to_string(RND->getFromIntTo(1, 6)));

						switch (iter->getWall())
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
					SOUNDMANAGER->play("cauldron_hit");

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

			if (_isMove)
			{
				PLAYER->setIsMove(true);
				CAMERA->setMaxCol(MAX_STAGE1_COL);
			}
			else
			{
				// �÷��̾� ��ġ ��ǥ ����
				PLAYER->setNextIdxX(PLAYER->getPosIdxX());
				PLAYER->setNextIdxY(PLAYER->getPosIdxY());
			}
		}
		else
		{
			BEAT->setIsMissed(true);
		}

		PLAYER->setNextDirection(PLAYER_DIRECTION::NONE);
		_isMove = false;
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

HRESULT GameScene::tileSet(vector<Tile>& _vTile, TILE_TYPE type)
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
			if (!_vTile[vIndex].getIsExist()) continue;

			// �÷��̾�� Ÿ�ϰ��� �Ÿ�
			int distance = sqrt(pow(_vTile[vIndex].getIdxX() - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex].getIdxY() - PLAYER->getPosIdxY(), 2));

			// �÷��̾�� Ÿ�ϰ��� �Ÿ��� ���� ���İ�
			int _alpha = getAlphaSet(distance, PLAYER->getLightPower());

			if (distance < PLAYER->getLightPower() || _vTile[vIndex].getIsLight())
			{
				switch (type)
				{
				case TILE_TYPE::TERRAIN:
					IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
						_vTile[vIndex].getFrameX(),
						_vTile[vIndex].getFrameY(),
						_alpha);
					break;
				case TILE_TYPE::WALL:
					IMAGEMANAGER->findImage("wall1")->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE) - 32,
						_vTile[vIndex].getFrameX(),
						_vTile[vIndex].getFrameY(),
						_alpha);
					break;
				case TILE_TYPE::DECO:
					break;
				}

				if (!_vTile[vIndex].getIsLight())
				{
					_vTile[vIndex].setIsLight(true);
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

void GameScene::showTileNum(vector<Tile> _vTile)
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
			sprintf_s(strIdx, "[%d, %d]", _vTile[vIndex].getIdxY(), _vTile[vIndex].getIdxX());

			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strIdx, strlen(strIdx));
		}
	}
}

void GameScene::showTileDist(vector<Tile> _vTile)
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

			int distance = sqrt(pow(_vTile[vIndex].getIdxX() - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex].getIdxY() - PLAYER->getPosIdxY(), 2));

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strDist, strlen(strDist));
		}
	}
}
