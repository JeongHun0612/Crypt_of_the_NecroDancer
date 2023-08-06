#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "../../../2DFrameWork/ManagerClass/FileManager.h"
#include "TileMap.h"

HRESULT TileMap::init(int currentScene)
{
	_vTiles.clear();
	_isLobby = false;
	_isNextStage = false;

	switch (currentScene)
	{
	case 0:
		_vEnemy.clear();
		_vItem.clear();

		FileManager::loadTileMapFile("Lobby_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
		FileManager::loadTileMapFile("Lobby_Wall.txt", _vWallTile, TILE_TYPE::WALL);

		_vTiles.push_back(_vTerrainTile);
		_vTiles.push_back(_vWallTile);

		for (int i = 0; i < _vTerrainTile.size(); i++)
		{
			if (!_vTerrainTile[i]->_isExist) continue;

			_vTerrainTile[i]->_isLight = true;
			_vTerrainTile[i]->_alpha = 255;

			_vWallTile[i]->_isLight = true;
			_vWallTile[i]->_alpha = 255;
		}

		_tileMaxCol = MAX_LOBBY_COL;
		_tileMaxRow = MAX_LOBBY_ROW;

		_isLobby = true;
		break;
	case 1:
		// 타일 초기화
		FileManager::loadTileMapFile("Stage1_1_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
		FileManager::loadTileMapFile("Stage1_1_Wall.txt", _vWallTile, TILE_TYPE::WALL);

		_vTiles.push_back(_vTerrainTile);
		_vTiles.push_back(_vWallTile);

		_tileMaxCol = MAX_STAGE1_1_COL;
		_tileMaxRow = MAX_STAGE1_1_ROW;

		// 애너미 초기화
		FileManager::loadEnemyFile("Stage1_1_Enemy.txt", _vEnemy, _vTiles, _tileMaxCol);

		// 아이템 초기화
		FileManager::loadItemFile("Stage1_1_Item.txt", _vItem, _tileMaxCol);

		// 다음 스테이지 계단
		_stairTileIdx = 22 * _tileMaxCol + 4;

		break;
	case 2:
		// 타일 초기화
		FileManager::loadTileMapFile("Stage1_2_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
		FileManager::loadTileMapFile("Stage1_2_Wall.txt", _vWallTile, TILE_TYPE::WALL);

		_vTiles.push_back(_vTerrainTile);
		_vTiles.push_back(_vWallTile);

		_tileMaxCol = MAX_STAGE1_2_COL;
		_tileMaxRow = MAX_STAGE1_2_ROW;

		// 애너미 초기화
		FileManager::loadEnemyFile("Stage1_2_Enemy.txt", _vEnemy, _vTiles, _tileMaxCol);

		// 아이템 초기화
		FileManager::loadItemFile("Stage1_2_Item.txt", _vItem, _tileMaxCol);

		// 다음 스테이지 계단
		_stairTileIdx = 20 * _tileMaxCol + 4;

		break;
	case 3:
		FileManager::loadTileMapFile("Boss_Terrain.txt", _vTerrainTile, TILE_TYPE::TERRAIN);
		FileManager::loadTileMapFile("Boss_Wall.txt", _vWallTile, TILE_TYPE::WALL);

		_vTiles.push_back(_vTerrainTile);
		_vTiles.push_back(_vWallTile);

		_tileMaxCol = MAX_BOSS_COL;
		_tileMaxRow = MAX_BOSS_ROW;

		// 애너미 초기화
		FileManager::loadEnemyFile("Boss_Enemy.txt", _vEnemy, _vTiles, _tileMaxCol);

		// 다음 스테이지 계단
		_stairTileIdx = 3 * _tileMaxCol + 8;
		break;
	}

	if (!_isLobby)
	{
		for (int i = 0; i < _vTerrainTile.size(); i++)
		{
			_vTerrainTile[i]->_alpha = 80;
			_vWallTile[i]->_alpha = 80;
		}
	}

	return S_OK;
}

void TileMap::update(void)
{
	// 계단 잠금 해제
	if (PLAYER->getIsNextStage())
	{
		_vTerrainTile[_stairTileIdx]->_frameY = 0;
	}

	// 바닥 타일 타입이 계단일 시 씬 변경
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::OPEN_STAIR)
	{
		_isNextStage = true;
	}
}

void TileMap::relese(void)
{
}

void TileMap::render(HDC hdc)
{
	// 타일 출력
	tileSet(hdc, _vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(hdc, _vWallTile, TILE_TYPE::WALL);

	if (!_isLobby)
	{
		getShowTileBFS(_vShowNode);

		for (int i = 0; i < _vTerrainTile.size(); i++)
		{
			_vTerrainTile[i]->_alpha = 80;
			_vWallTile[i]->_alpha = 80;
		}

		for (auto iter = _vShowNode.begin(); iter != _vShowNode.end(); ++iter)
		{
			_vTerrainTile[(*iter).tileIdx]->_alpha = (*iter).alpha;
			_vWallTile[(*iter).tileIdx]->_alpha = (*iter).alpha;
		}
	}

	// 아이템 출력
	for (auto iter = _vItem.begin(); iter != _vItem.end(); ++iter)
	{
		(*iter)->render(hdc);
	}

	// 몬스터 출력
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(hdc);
	}

	// 미니맵 출력
	showMiniMap(hdc);


	// 디버그 모드
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(hdc);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(hdc);
	}
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = (HPEN)CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		// 그릴 것 (애너미 충돌 영역, 비트 성공 영역)
		showEnemyCollider(hdc);
		//DrawRectMake(hdc, BEAT->getBeatRate());

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}
}

void TileMap::addEnemyList(Enemy* enemy)
{
	_vEnemy.push_back(enemy);
}


void TileMap::tileSet(HDC hdc, vector<Tile*> vTile, TILE_TYPE tileType)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdx().x + j;
			int curIdxY = PLAYER->getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > _tileMaxCol - 1) continue;
			if (curIdxY < 0 || curIdxY > _tileMaxRow - 1) continue;

			int tileIdx = (curIdxY * _tileMaxCol) + curIdxX;

			// 타일을 그리지 않거나 밝혀지지 않은 부분으면 continue;
			if (!vTile[tileIdx]->_isExist || !vTile[tileIdx]->_isLight) continue;

			switch (tileType)
			{
			case TILE_TYPE::TERRAIN:
				IMAGEMANAGER->findImage("tile_terrain")->frameAlphaRender(hdc,
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					vTile[tileIdx]->_frameX,
					vTile[tileIdx]->_frameY,
					vTile[tileIdx]->_alpha);
				break;
			case TILE_TYPE::WALL:
				IMAGEMANAGER->findImage("tile_wall")->frameAlphaRender(hdc,
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE) - 32,
					vTile[tileIdx]->_frameX,
					vTile[tileIdx]->_frameY,
					vTile[tileIdx]->_alpha);
				break;
			case TILE_TYPE::DECO:
				break;
			}
		}
	}
}

void TileMap::getShowTileBFS(vector<Node>& vShowNode)
{
	vShowNode.clear();

	Vec2 direction[4] = { {-1,0}, {0, -1}, {1, 0}, {0, 1} };

	queue<Node> tileNodeQueue;

	Node curNode;
	curNode.posIdx = { PLAYER->getPosIdx().x, PLAYER->getPosIdx().y };
	curNode.alpha = 255;
	curNode.isCollider = false;
	curNode.tileIdx = (curNode.posIdx.y * _tileMaxCol) + curNode.posIdx.x;

	tileNodeQueue.push(curNode);
	vShowNode.push_back(curNode);

	while (!tileNodeQueue.empty())
	{
		Node curNode = tileNodeQueue.front();
		tileNodeQueue.pop();

		if (curNode.isCollider) continue;

		for (int i = 0; i < 4; i++)
		{
			Vec2 nextIdx = { curNode.posIdx.x + direction[i].x, curNode.posIdx.y + direction[i].y };
			int nextTileIdx = (nextIdx.y * _tileMaxCol) + nextIdx.x;

			if (nextTileIdx < 0 || nextTileIdx > _vTiles[0].size()) continue;
			if (nextIdx.x < 0 || nextIdx.y < 0 || nextIdx.x > _tileMaxCol - 1 || nextIdx.y > _tileMaxRow - 1) continue;
			if (_vTiles[0][nextTileIdx]->_isSearch) continue;

			int depth = abs(nextIdx.x - PLAYER->getPosIdx().x) + abs(nextIdx.y - PLAYER->getPosIdx().y);

			if (depth > PLAYER->getLightPower()) break;

			Node nextNode;
			nextNode.posIdx = { nextIdx.x, nextIdx.y };
			nextNode.alpha = 255 - (10 * depth);
			//nextNode.alpha = 255;
			nextNode.isCollider = _vTiles[1][nextTileIdx]->_isCollider;
			nextNode.tileIdx = nextTileIdx;

			tileNodeQueue.push(nextNode);
			vShowNode.push_back(nextNode);

			_vTiles[0][nextTileIdx]->_isSearch = true;

			if (!_vTiles[0][nextTileIdx]->_isLight)
			{
				_vTiles[0][nextTileIdx]->_isLight = true;
				_vTiles[1][nextTileIdx]->_isLight = true;
			}
		}
	}

	for (auto iter = _vTiles[0].begin(); iter != _vTiles[0].end(); ++iter)
	{
		(*iter)->_isSearch = false;
	}
}

void TileMap::showTileNum(HDC hdc)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdx().x + j;
			int curIdxY = PLAYER->getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > _tileMaxCol - 1) continue;
			if (curIdxY < 0 || curIdxY > _tileMaxRow - 1) continue;

			int tileIdx = curIdxY * _tileMaxCol + curIdxX;

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _vTerrainTile[tileIdx]->_idxY, _vTerrainTile[tileIdx]->_idxX);

			TextOut(hdc, CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strIdx, strlen(strIdx));
		}
	}
}

void TileMap::showTileDist(HDC hdc)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdx().x + j;
			int curIdxY = PLAYER->getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > _tileMaxCol - 1) continue;
			if (curIdxY < 0 || curIdxY > _tileMaxRow - 1) continue;

			int vIndex = curIdxY * _tileMaxCol + curIdxX;

			int distance = abs(_vTerrainTile[vIndex]->_idxX - PLAYER->getPosIdx().x) + abs(_vTerrainTile[vIndex]->_idxY - PLAYER->getPosIdx().y);

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(hdc, CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strDist, strlen(strDist));
		}
	}
}

void TileMap::showEnemyCollider(HDC hdc)
{
	for (auto iter = _vTerrainTile.begin(); iter != _vTerrainTile.end(); ++iter)
	{
		if ((*iter)->_isCollider)
		{
			// 몬스터 충돌체 영역
			RectangleMake(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdx().x - (*iter)->_idxX) * 64,
				CAMERA->getPos().y - (PLAYER->getPosIdx().y - (*iter)->_idxY) * 64,
				64, 64);
		}
	}
}

void TileMap::showMiniMap(HDC hdc)
{
	// 미니맵 출력
	for (int i = 0; i < _vTerrainTile.size(); i++)
	{
		if (!_vTerrainTile[i]->_isLight) continue;
		//if (!_vTerrainTile[i]->_isLight || !_vTerrainTile[i]->_isExist) continue;

		// 바닥 타일 출력
		switch (_vTerrainTile[i]->_terrainType)
		{
		case TERRAIN_TYPE::GROUND:
			IMAGEMANAGER->findImage("min_rect_normal")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		case TERRAIN_TYPE::LOCK_STAIR: case TERRAIN_TYPE::OPEN_STAIR:
			IMAGEMANAGER->findImage("min_rect_stair")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		}

		// 벽 타일 출력
		if (!_vWallTile[i]->_isLight || !_vWallTile[i]->_isExist) continue;

		switch (_vWallTile[i]->_wallType)
		{
		case WALL_TYPE::BORDER:
			IMAGEMANAGER->findImage("min_rect_end")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		case WALL_TYPE::DOOR:
			IMAGEMANAGER->findImage("min_rect_door")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		case WALL_TYPE::GOLDWALL:
			IMAGEMANAGER->findImage("min_rect_shop")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		case WALL_TYPE::BRICK:
			IMAGEMANAGER->findImage("min_rect_wall2")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		default:
			IMAGEMANAGER->findImage("min_rect_end_else")->render(hdc,
				1150 - (_tileMaxCol * 6) / 2 + (_vTerrainTile[i]->_idxX * 6),
				600 - (_tileMaxRow * 6) / 2 + (_vTerrainTile[i]->_idxY * 6));
			break;
		}
	}

	// 적 출력
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (!_vTerrainTile[_vEnemy[i]->getCurTileIdx()]->_isLight) continue;

		IMAGEMANAGER->findImage("min_rect_enemy")->render(hdc,
			1150 - (_tileMaxCol * 6) / 2 + (_vEnemy[i]->getPosIdx().x * 6),
			600 - (_tileMaxRow * 6) / 2 + (_vEnemy[i]->getPosIdx().y * 6));
	}

	// 플레이어 출력
	IMAGEMANAGER->findImage("min_rect_player")->render(hdc,
		1150 - (_tileMaxCol * 6) / 2 + (PLAYER->getPosIdx().x * 6),
		600 - (_tileMaxRow * 6) / 2 + (PLAYER->getPosIdx().y * 6));
}
