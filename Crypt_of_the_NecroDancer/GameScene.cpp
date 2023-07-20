#include "Stdafx.h"
#include "GameScene.h"
#include "FileManager.h"

HRESULT GameScene::init(void)
{
	SOUNDMANAGER->play("stage1-1", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// 타일 초기화
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();


	// 플레이어 위치 초기화
	PLAYER->setPosIdxX(25);
	PLAYER->setPosIdxY(20);
	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());

	// 비트 초기화
	BEAT->init();

	// 애너미 초기화
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


			// 타일 검사
			for (int i = TILEMAP->getStartIdx(); i < TILEMAP->getStartIdx() + INSPRECTION_RANGE; i++)
			{
				// 범위 밖 검사
				if (i > _vTerrainTile.size() - 1) break;


				// 다음 스테이지 이동
				if (_vTerrainTile[i].getIdxX() == PLAYER->getNextIdxX() && _vTerrainTile[i].getIdxY() == PLAYER->getNextIdxY() && _vTerrainTile[i].getTerrain() == TERRAIN::STAIR)
				{
					cout << "다음 스테이지 이동" << endl;
				}

				// 충돌체 발견 시
				if (_vWallTile[i].getIdxX() == PLAYER->getNextIdxX() && _vWallTile[i].getIdxY() == PLAYER->getNextIdxY() && _vWallTile[i].getIsCollider())
				{
					_isMove = false;
					PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());

					// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
					if (_vWallTile[i].getHardNess() > PLAYER->getCurShovel()->getHardNess())
					{
						SOUNDMANAGER->play("dig_fail");
					}
					else
					{
						// 벽 부수기
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
						// 몬스터 객체 삭제 및 벡터 삭제
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

		// 움직일 때 마다 setStartIndex 갱신
		TILEMAP->setStartIdx(PLAYER->getPosIdxX(), PLAYER->getPosIdxY(), MAX_STAGE1_COL);
	}
}

void GameScene::render(void)
{
	// 타일 출력
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

	// 몬스터 출력
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
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

			// 타일을 그리지 않겠다면 continue
			if (!_vTile[vIndex].getIsExist()) continue;

			// 플레이어와 타일간의 거리
			int distance = sqrt(pow(_vTile[vIndex].getIdxX() - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex].getIdxY() - PLAYER->getPosIdxY(), 2));

			// 플레이어와 타일간의 거리에 따른 알파값
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
