#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	GameScene::init();

	_isMove = false;

	// 타일 초기화
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	// 플레이어 초기화
	PLAYER->init(5, 5);

	// UI 초기화
	UIMANAGER->init();

	// 애너미 초기화
	ENEMYMANAGER->init();

	// 사운드 플레이
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

	int _curIdx = MAX_LOBBY_COL * PLAYER->getPosIdxY() + PLAYER->getPosIdxX();
	int _nextIdx = MAX_LOBBY_COL * PLAYER->getNextIdxY() + PLAYER->getNextIdxX();

	int _leftIdx = _curIdx - 1;
	int _rightIdx = _curIdx + 1;
	int _topIdx = _curIdx - MAX_LOBBY_COL;
	int _bottomIdx = _curIdx + MAX_LOBBY_COL;


	// 아래 쪽에 타일이 있을 시 그림자 숨기기
	if (_vWallTile[_bottomIdx]->_idxX == PLAYER->getPosIdxX() && _vWallTile[_bottomIdx]->_idxY == PLAYER->getPosIdxY() + 1 && _vWallTile[_bottomIdx]->_isCollider)
	{
		PLAYER->setShadowAlpha(0);
	}

	// 키 입력이 있을 시 (좌 / 우 / 상 / 하)
	if (PLAYER->getNextDirection() != PLAYER_DIRECTION::NONE)
	{
		_isMove = true;
		PLAYER->setCurDirection(PLAYER->getNextDirection());

		// 바닥 타일 검사
		if (_vTerrainTile[_nextIdx]->_terrain == TERRAIN::STAIR)
		{
			SCENEMANAGER->changeScene("game");
		}

		// 충돌체 발견 시
		if (_vWallTile[_nextIdx]->_isCollider)
		{
			_isMove = false;

			// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
			if (_vWallTile[_nextIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
			{
				PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());
				SOUNDMANAGER->play("dig_fail");
			}
			else
			{
				// 벽 부수기
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

		PLAYER->setNextDirection(PLAYER_DIRECTION::NONE);
	}
}

void LobbyScene::render()
{
	// 바닥 타일 출력
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// 플레이어 출력
	PLAYER->render(getMemDC());

	// UI 출력
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

			// 타일을 그리지 않겠다면 continue
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