#include "Stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init()
{
	// 타일 초기화
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	_tileMaxCol = MAX_LOBBY_COL;
	_tileMaxRow = MAX_LOBBY_ROW;

	// 플레이어 초기화
	PLAYER->init(5, 5);

	// 비트 초기화
	BEAT->setIsBeat(true);

	// UI 초기화
	UIMANAGER->init();

	// 사운드 플레이
	SOUNDMANAGER->play("lobby", 0.5f);

	return S_OK;
}

void TestScene::release()
{
	SOUNDMANAGER->stop("lobby");
}

void TestScene::update()
{
	CAMERA->update();

	PLAYER->update();
}

void TestScene::render()
{
	// 타일 출력
	_drawTileIdx = tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	//tileSet(_vWallTile, TILE_TYPE::WALL);

	for (auto iter = _drawTileIdx.begin(); iter != _drawTileIdx.end(); ++iter) {

		IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _vTerrainTile[*iter]->_idxX) * 64,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _vTerrainTile[*iter]->_idxY) * 64,
			_vTerrainTile[*iter]->_frameX,
			_vTerrainTile[*iter]->_frameY,
			255);
	}


	// 플레이어 출력
	PLAYER->render(getMemDC());

	// UI 출력
	UIMANAGER->render(getMemDC());

	// 디버그 모드
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_vTerrainTile);
	}
}


unordered_set<int> TestScene::tileSet(vector<Tile*> vTile, TILE_TYPE tileType)
{
	int direction[4] = { -1, -_tileMaxCol, 1, _tileMaxCol };

	queue<int> tileIdxQueue;
	unordered_set<int> vTileIdx;
	//vector<int> vTileIdx;

	int curIdxX = PLAYER->getPosIdx().x;
	int curIdxY = PLAYER->getPosIdx().y;

	int curTileIdx = (curIdxY * _tileMaxCol) + curIdxX;

	//int count = 1 + pow(4.0f, 4.0f);
	int count = 2;

	for (int i = 1; i < 4; i++)
	{
		count += (4 * i);
	}
	
	tileIdxQueue.push(curTileIdx);
	vTileIdx.insert(curTileIdx);

	while (count > 0)
	{
		int curTileIdx = tileIdxQueue.front();
		tileIdxQueue.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextTileIdx = curTileIdx + direction[i];

			if (nextTileIdx < 0 || nextTileIdx > vTile.size()) continue;

			if (vTile[nextTileIdx]->_isLight || !vTile[nextTileIdx]->_isExist) continue;

			//int distance = abs(vTile[nextTileIdx]->_idxX - PLAYER->getPosIdx().x) + abs(vTile[nextTileIdx]->_idxY - PLAYER->getPosIdx().y);

			//if (distance > 5) break;

			tileIdxQueue.push(nextTileIdx);
			vTileIdx.insert(nextTileIdx);
			vTile[nextTileIdx]->_isLight = true;
		}

		count--;
	}

	for (auto iter = vTile.begin(); iter != vTile.end(); ++iter)
	{
		(*iter)->_isLight = false;
	}

	cout << vTileIdx.size() << endl;

	return vTileIdx;


	//while (abs(vTile[tileIdxQueue.back()]->_idxX - curIdxX) + abs(vTile[tileIdxQueue.back()]->_idxY - curIdxY) < 4)
	//{
	//	tileIdxQueue.pop();

	//	for (int i = 0; i < 4; i++)
	//	{
	//		int nextTileIdx = curTileIdx + direction[i];
	//		tileIdxQueue.push(nextTileIdx);

	//		IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
	//			CAMERA->getPos().x - (curIdxX - vTile[nextTileIdx]->_idxX) * 64,
	//			CAMERA->getPos().y - (curIdxY - vTile[nextTileIdx]->_idxY) * 64,
	//			vTile[nextTileIdx]->_frameX,
	//			vTile[nextTileIdx]->_frameY,
	//			255);
	//	}
	//}

	//for (int i = -7; i < 8; i++)
	//{
	//	for (int j = -11; j < 12; j++)
	//	{
	//		int curIdxX = PLAYER->getPosIdx().x + j;
	//		int curIdxY = PLAYER->getPosIdx().y + i;

	//		if (curIdxX < 0 || curIdxX > _tileMaxCol - 1) continue;
	//		if (curIdxY < 0 || curIdxY > _tileMaxRow - 1) continue;

	//		int vIndex = (curIdxY * _tileMaxCol) + curIdxX;

	//		// 타일을 그리지 않겠다면 continue
	//		if (!vTile[vIndex]->_isExist) continue;

	//		// 플레이어와 타일간의 거리
	//		int distance = sqrt(pow(vTile[vIndex]->_idxX - PLAYER->getPosIdx().x, 2) + pow(vTile[vIndex]->_idxY - PLAYER->getPosIdx().y, 2));

	//		// 플레이어와 타일간의 거리에 따른 알파값
	//		int _alpha;
	//		_alpha = (_isLobby) ? 255 : getAlphaSet(distance, PLAYER->getLightPower());

	//		if (distance < PLAYER->getLightPower() || vTile[vIndex]->_isLight)
	//		{
	//			switch (tileType)
	//			{
	//			case TILE_TYPE::TERRAIN:
	//				IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
	//					CAMERA->getPos().x + (j * TILESIZE),
	//					CAMERA->getPos().y + (i * TILESIZE),
	//					vTile[vIndex]->_frameX,
	//					vTile[vIndex]->_frameY,
	//					_alpha);
	//				break;
	//			case TILE_TYPE::WALL:
	//				IMAGEMANAGER->findImage("wall1")->frameAlphaRender(getMemDC(),
	//					CAMERA->getPos().x + (j * TILESIZE),
	//					CAMERA->getPos().y + (i * TILESIZE) - 32,
	//					vTile[vIndex]->_frameX,
	//					vTile[vIndex]->_frameY,
	//					_alpha);
	//				break;
	//			case TILE_TYPE::DECO:
	//				break;
	//			}

	//			if (!vTile[vIndex]->_isLight)
	//			{
	//				vTile[vIndex]->_isLight = true;
	//			}
	//		}
	//	}
	//}
}
