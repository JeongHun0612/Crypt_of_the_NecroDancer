#include "Stdafx.h"
#include "GameScene.h"
#include "FileManager.h"

HRESULT GameScene::init(void)
{
	SOUNDMANAGER->play("stage1-1", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// 타일 초기화
	FileManager::loadTileMapFile("Stage1-1_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Stage1-1_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	// 플레이어 초기화
	PLAYER->init();
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());

	_nextDirection = PLAYER->getCurDirection();

	// 비트 초기화
	BEAT->init();

	// UI 초기화
	UIMANAGER->init();

	// 애너미 초기화
	Slime* _slime = new Slime_Green;
	_slime->init(3, 3, 1, 3);

	_enemyTile[3][3].idxY = 3;
	_enemyTile[3][3].idxX = 3;

	_vSlime.push_back(_slime);

	Slime* _slime2 = new Slime_Blue;
	_slime2->init(3, 5, 2, 4);

	_enemyTile[3][5].idxY = 3;
	_enemyTile[3][5].idxX = 5;

	_vSlime.push_back(_slime2);

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

	for (auto iter = _vSlime.begin(); iter != _vSlime.end(); ++iter)
	{
		(*iter)->update();
	}

	// 플레이어 키입력 동작
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

	// 키 입력이 있을 시 (좌 / 우 / 상 / 하)
	if (_nextDirection != PLAYER_DIRECTION::NONE)
	{
		if (BEAT->getBeat())
		{
			_isMove = true;
			BEAT->setIsSuccess(true);
			PLAYER->setCurDirection(_nextDirection);

			for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
			{
				// 다음 스테이지 이동
				if (iter->idxX == PLAYER->getNextIdxX() && iter->idxY == PLAYER->getNextIdxY() && iter->terrain == TERRAIN::STAIR)
				{
					cout << "다음 스테이지 이동" << endl;
				}
			}

			for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
			{
				// 충돌체 발견 시
				if (iter->idxX == PLAYER->getNextIdxX() && iter->idxY == PLAYER->getNextIdxY() && iter->isColiider)
				{
					_isMove = false;

					// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
					if (iter->hardness > PLAYER->getCurShovel()->getHardNess())
					{
						PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());
						SOUNDMANAGER->play("dig_fail");
					}
					else
					{
						// 벽 부수기
						iter->isExist = false;
					}
				}
			}

			for (auto iter = _vSlime.begin(); iter != _vSlime.end();)
			{
				if ((*iter)->getIdxX() == PLAYER->getNextIdxX() && (*iter)->getIdxY() == PLAYER->getNextIdxY())
				{
					_isMove = false;
					CAMERA->cameraShake(10);
					PLAYER->getCurWeapon()->setIsAttack(true);
					SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));

					(*iter)->setCurHP((*iter)->getCurHP() - PLAYER->getCurWeapon()->getPower());

					if ((*iter)->getCurHP() <= 0)
					{
						// 몬스터 소지금
						UIMANAGER->addCoin((*iter)->getIdxX(), (*iter)->getIdxY(), (*iter)->getCoinCount());

						// 몬스터 객체 삭제 및 벡터 삭제
						delete((*iter));
						iter = _vSlime.erase(iter);
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
	}
}

void GameScene::render(void)
{
	// 타일 출력
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

	// 몬스터 출력
	for (auto iter = _vSlime.begin(); iter != _vSlime.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// UI 출력
	UIMANAGER->render(getMemDC());

	// 플레이어 출력
	PLAYER->render(getMemDC());

	// 비트 출력
	BEAT->render(getMemDC());
}

void GameScene::tileSet(vector<Tile>& _vTile, TILE_TYPE type)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdxX() + j;
			int curIdxY = PLAYER->getPosIdxY() + i;

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = (curIdxY * MAX_ROBBY_COL) + curIdxX;

			// 타일을 그리지 않겠다면 continue
			if (!_vTile[vIndex].isExist) continue;

			// 플레이어와 타일간의 거리
			int distance = sqrt(pow(_vTile[vIndex].idxX - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex].idxY - PLAYER->getPosIdxY(), 2));

			// 플레이어와 타일간의 거리에 따른 알파값
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

				if (!_vTile[vIndex].isLight)
				{
					_vTile[vIndex].isLight = true;
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

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;
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

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = curIdxY * MAX_ROBBY_COL + curIdxX;

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _vTile[vIndex].idxY, _vTile[vIndex].idxX);

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
