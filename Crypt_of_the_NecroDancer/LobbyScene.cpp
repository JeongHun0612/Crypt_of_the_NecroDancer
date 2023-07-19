#include "Stdafx.h"
#include "LobbyScene.h"
#include "FileManager.h"

HRESULT LobbyScene::init()
{
	SOUNDMANAGER->play("lobby", 0.5f);

	_terrainImg = IMAGEMANAGER->findImage("terrain1");
	_wallImg = IMAGEMANAGER->findImage("wall1");

	// 타일 초기화
	FileManager::loadTileMapFile("Lobby_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
	FileManager::loadTileMapFile("Lobby_Wall.txt", _vWallTile, TILE_TYPE::WALL);

	cout << _vTerrainTile.size() << endl;

	// 플레이어 초기화
	PLAYER->init();
	PLAYER->setPosIdxX(5);
	PLAYER->setPosIdxY(5);

	PLAYER->setNextIdxX(PLAYER->getPosIdxX());
	PLAYER->setNextIdxY(PLAYER->getPosIdxY());

	_nextDirection = PLAYER->getCurDirection();

	// UI 초기화
	UIMANAGER->init();

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

		for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
		{
			// 다음 스테이지 이동
			if (iter->getIdxX() == PLAYER->getNextIdxX() && iter->getIdxY() == PLAYER->getNextIdxY() && iter->getTerrain() == TERRAIN::STAIR)
			{
				SCENEMANAGER->changeScene("game");
			}
		}

		for (auto iter = _vWallTile.begin(); iter != _vWallTile.end(); ++iter)
		{
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
					iter->setIsExist(false);
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

			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;

			int vIndex = (curIdxY * MAX_ROBBY_COL) + curIdxX;

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