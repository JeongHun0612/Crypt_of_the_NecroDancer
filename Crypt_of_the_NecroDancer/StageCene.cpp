#include "Stdafx.h"
#include "GameScene.h"
#include "FileManager.h"

HRESULT GameScene::init(void)
{
	// 비트 초기화
	BEAT->init();

	// 타일 초기화
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	// 플레이어 위치 초기화
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);
	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());
	PLAYER->setCurDirection(PLAYER_DIRECTION::NONE);
	PLAYER->setNextDirection(PLAYER->getCurDirection());

	// 애너미 초기화
	_vEnemy = ENEMYMANAGER->getEnemyList();

	// 매개 변수 초기화
	_isMove = false;

	// 사운드 플레이
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

	// 플레이어 키입력 동작
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


	// 아래 쪽에 타일이 있을 시 그림자 숨기기
	if (_vWallTile[_bottomIdx]->_idxX == PLAYER->getPosIdxX() && _vWallTile[_bottomIdx]->_idxY == PLAYER->getPosIdxY() + 1 && _vWallTile[_bottomIdx]->_isCollider)
	{
		PLAYER->setShadowAlpha(0);
	}

	// 키 입력이 있을 시 (좌 / 우 / 상 / 하)
	if (PLAYER->getNextDirection() != PLAYER_DIRECTION::NONE)
	{
		if (BEAT->getBeat())
		{
			_isMove = true;
			BEAT->setIsSuccess(true);
			PLAYER->setCurDirection(PLAYER->getNextDirection());

			// 바닥 타일 검사
			if (_vTerrainTile[_nextIdx]->_terrain == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}

			// 충돌체 발견 시
			if (TILEMAP->getStage1Wall()[_nextIdx]->_isCollider)
			{
				_isMove = false;
				PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());

				// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
				if (_vWallTile[_nextIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
				{
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// 벽 부수기
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

			// 애너미 검사
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
						// 몬스터 객체 삭제 및 벡터 삭제
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

			// 움직이기
			if (_isMove)
			{
				PLAYER->setIsMove(true);
			}
			else
			{
				// 플레이어 Next좌표 초기화
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
	// 타일 출력
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// 플레이어 출력
	PLAYER->render(getMemDC());

	// 몬스터 출력
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// 디버그 모드
	if (KEYMANAGER->isToggleKey(VK_F1) && !_vTerrainTile.empty())
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2) && !_vTerrainTile.empty())
	{
		showTileDist(_vTerrainTile);
	}

	// 비트 출력
	BEAT->render(getMemDC());

	// UI 출력
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

			// 타일을 그리지 않겠다면 continue
			if (!_vTile[vIndex]->_isExist) continue;

			// 플레이어와 타일간의 거리
			int distance = sqrt(pow(_vTile[vIndex]->_idxX - PLAYER->getPosIdxX(), 2) + pow(_vTile[vIndex]->_idxY - PLAYER->getPosIdxY(), 2));

			// 플레이어와 타일간의 거리에 따른 알파값
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
