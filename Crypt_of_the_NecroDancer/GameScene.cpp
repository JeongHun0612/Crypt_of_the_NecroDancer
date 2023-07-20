#include "Stdafx.h"
#include "GameScene.h"
#include "FileManager.h"

HRESULT GameScene::init(void)
{
	SOUNDMANAGER->play("stage1-1", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// Ÿ�� �ʱ�ȭ
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();


	// �÷��̾� ��ġ �ʱ�ȭ
	PLAYER->setPosIdxX(25);
	PLAYER->setPosIdxY(20);
	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());

	// ��Ʈ �ʱ�ȭ
	BEAT->init();

	// �ֳʹ� �ʱ�ȭ
	ENEMYMANAGER->init();
	_vEnemy = ENEMYMANAGER->getEnemyList();

	_isMove = false;

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
		if (BEAT->getBeat())
		{
			_isMove = true;
			BEAT->setIsSuccess(true);
			PLAYER->setCurDirection(_nextDirection);


			// Ÿ�� �˻�
			for (int i = TILEMAP->getStartIdx(); i < TILEMAP->getStartIdx() + INSPRECTION_RANGE; i++)
			{
				// ���� �� �˻�
				if (i > _vTerrainTile.size() - 1) break;


				// ���� �������� �̵�
				if (_vTerrainTile[i].getIdxX() == PLAYER->getNextIdxX() && _vTerrainTile[i].getIdxY() == PLAYER->getNextIdxY() && _vTerrainTile[i].getTerrain() == TERRAIN::STAIR)
				{
					cout << "���� �������� �̵�" << endl;
				}

				// �浹ü �߰� ��
				if (_vWallTile[i].getIdxX() == PLAYER->getNextIdxX() && _vWallTile[i].getIdxY() == PLAYER->getNextIdxY() && _vWallTile[i].getIsCollider())
				{
					_isMove = false;
					PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());

					// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
					if (_vWallTile[i].getHardNess() > PLAYER->getCurShovel()->getHardNess())
					{
						SOUNDMANAGER->play("dig_fail");
					}
					else
					{
						// �� �μ���
						_vWallTile[i].setIsExist(false);
						_vWallTile[i].setIsCollider(false);
						CAMERA->cameraShake(15);
						SOUNDMANAGER->play("dig" + to_string(RND->getFromIntTo(1, 6)));

						switch (_vWallTile[i].getWall())
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

			for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
			{
				if ((*iter)->getIdxX() == PLAYER->getNextIdxX() && (*iter)->getIdxY() == PLAYER->getNextIdxY())
				{
					_isMove = false;
					CAMERA->cameraShake(15);
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
				}
			}

			if (_isMove)
			{
				PLAYER->setIsMove(true);
				PLAYER->setPosIdxX(PLAYER->getNextIdxX());
				PLAYER->setPosIdxY(PLAYER->getNextIdxY());
			}
		}
		else
		{
			BEAT->setIsMissed(true);
		}

		_nextDirection = PLAYER_DIRECTION::NONE;
		PLAYER->setNextIdxX(PLAYER->getPosIdxX());
		PLAYER->setNextIdxY(PLAYER->getPosIdxY());

		// ������ �� ���� setStartIndex ����
		TILEMAP->setStartIdx(PLAYER->getPosIdxX(), PLAYER->getPosIdxY(), MAX_STAGE1_COL);
	}
}

void GameScene::render(void)
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	if (KEYMANAGER->isToggleKey(VK_F1) && !_vTerrainTile.empty())
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2) && !_vTerrainTile.empty())
	{
		showTileDist(_vTerrainTile);
	}

	// ���� ���
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// UI ���
	UIMANAGER->render(getMemDC());

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// ��Ʈ ���
	BEAT->render(getMemDC());
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
					_terrainImg->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
						_vTile[vIndex].getFrameX(),
						_vTile[vIndex].getFrameY(),
						_alpha);
					break;
				case TILE_TYPE::WALL:
					_wallImg->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
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

			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strIdx, strlen(strIdx));
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
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE), strDist, strlen(strDist));
		}
	}
}
