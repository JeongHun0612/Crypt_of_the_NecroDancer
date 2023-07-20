#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// 타일 초기화
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	// 플레이어 초기화
	PLAYER->init(5, 5);

	// UI 초기화
	UIMANAGER->init();

	_nextDirection = PLAYER->getCurDirection();

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
		_isMove = true;
		PLAYER->setCurDirection(_nextDirection);

		for (int i = TILEMAP->getStartIdx(); i < TILEMAP->getStartIdx() + INSPRECTION_RANGE; i++)
		{
			// 범위 밖 검사
			if (i > _vTerrainTile.size() - 1)
			{
				break;
			}

			// 다음 스테이지 이동
			if (_vTerrainTile[i].getIdxX() == PLAYER->getNextIdxX() && _vTerrainTile[i].getIdxY() == PLAYER->getNextIdxY() && _vTerrainTile[i].getTerrain() == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}

			// 충돌체 발견 시
			if (_vWallTile[i].getIdxX() == PLAYER->getNextIdxX() && _vWallTile[i].getIdxY() == PLAYER->getNextIdxY() && _vWallTile[i].getIsCollider())
			{
				_isMove = false;

				// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
				if (_vWallTile[i].getHardNess() > PLAYER->getCurShovel()->getHardNess())
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
			PLAYER->setPosIdxX(PLAYER->getNextIdxX());
			PLAYER->setPosIdxY(PLAYER->getNextIdxY());
		}

		PLAYER->setNextIdxX(PLAYER->getPosIdxX());
		PLAYER->setNextIdxY(PLAYER->getPosIdxY());
		_nextDirection = PLAYER_DIRECTION::NONE;


		// 움직일 때 마다 setStartIndex 갱신
		TILEMAP->setStartIdx(PLAYER->getPosIdxX(), PLAYER->getNextIdxY(), MAX_LOBBY_COL);
	}
}

void LobbyScene::render()
{
	// 타일 출력
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
				_terrainImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_vTile[vIndex].getFrameX(),
					_vTile[vIndex].getFrameY());
				break;
			case TILE_TYPE::WALL:
				_wallImg->frameRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					_vTile[vIndex].getFrameX(),
					_vTile[vIndex].getFrameY());
				break;
			case TILE_TYPE::DECO:
				break;
			}
		}
	}
}