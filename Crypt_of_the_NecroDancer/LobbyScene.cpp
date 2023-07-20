#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
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

	// 아래 쪽에 타일이 있을 시 그림자 숨기기
	for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
	{
		if (iter->getIdxX() == PLAYER->getPosIdxX() && (iter->getIdxY() == PLAYER->getNextIdxY() + 1 || iter->getIdxY() == PLAYER->getPosIdxY() + 1) && iter->getIsExist())
		{
			PLAYER->setShadowAlpha(0);
			break;
		}
	}

	// 키 입력이 있을 시 (좌 / 우 / 상 / 하)
	if (PLAYER->getNextDirection() != PLAYER_DIRECTION::NONE)
	{
		PLAYER->setShadowAlpha(130);
		PLAYER->setCurDirection(PLAYER->getNextDirection());

		// 바닥 타일 검사
		for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
		{
			// 다음 스테이지 이동
			if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getTerrain() == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}
		}

		// 벽 타일 검사
		for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
		{
			// 아래 쪽에 타일이 있을 시 그림자 숨기기
			if (iter->getIdxX() == PLAYER->getPosIdxX() && (iter->getIdxY() == PLAYER->getNextIdxY() + 1 || iter->getIdxY() == PLAYER->getPosIdxY() + 1) && iter->getIsExist())
			{
				PLAYER->setShadowAlpha(0);
			}

			// 충돌체 발견 시
			if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getIsCollider())
			{
				_isMove = false;

				// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
				if (iter->getHardNess() > PLAYER->getCurShovel()->getHardNess())
				{
					PLAYER->getCurShovel()->addShowShovel(PLAYER->getNextIdxX(), PLAYER->getNextIdxY());
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// 벽 부수기
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
			// 플레이어 위치 좌표 설정
			PLAYER->setNextIdxX(PLAYER->getPosIdxX());
			PLAYER->setNextIdxY(PLAYER->getPosIdxY());
		}

		PLAYER->setNextDirection(PLAYER_DIRECTION::NONE);
		_isMove = false;
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

			// 타일을 그리지 않겠다면 continue
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