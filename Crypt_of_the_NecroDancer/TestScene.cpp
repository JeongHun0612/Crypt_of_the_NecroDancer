#include "Stdafx.h"
#include "TestScene.h"


HRESULT TestScene::init()
{
	// 타일 초기화
	//_vTiles = TILEMAP->getLoobyTiles();
	//_vTerrainTile = TILEMAP->getLoobyTerrain();
	//_vWallTile = TILEMAP->getLoobyWall();

	//_tileMaxCol = MAX_LOBBY_COL;
	//_tileMaxRow = MAX_LOBBY_ROW;

	_tileMaxCol = MAX_STAGE1_1_COL;
	_tileMaxRow = MAX_STAGE1_1_ROW;


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
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	//_drawNode = tileSetTest(_vTiles);

	for (auto iter = _drawNode.begin(); iter != _drawNode.end(); ++iter)
	{
		_vTerrainTile[(*iter).tileIdx]->_alpha = (*iter).alpha;
		_vWallTile[(*iter).tileIdx]->_alpha = (*iter).alpha;
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


//vector<Node> TestScene::tileSetTest(vector<vector<Tile*>> vTiles)
//{
//	Vec2 direction[4] = { {-1,0}, {0, -1}, {1, 0}, {0, 1} };
//
//	queue<Node> tileNodeQueue;
//	vector<Node> vNodeList;
//
//	Node curNode;
//	curNode.posIdx = { PLAYER->getPosIdx().x, PLAYER->getPosIdx().y };
//	curNode.alpha = 255;
//	curNode.isCollider = false;
//	curNode.tileIdx = (curNode.posIdx.y * _tileMaxCol) + curNode.posIdx.x;
//
//	tileNodeQueue.push(curNode);
//	vNodeList.push_back(curNode);
//
//	while (!tileNodeQueue.empty())
//	{
//		Node curNode = tileNodeQueue.front();
//		tileNodeQueue.pop();
//
//		if (curNode.isCollider) continue;
//
//		for (int i = 0; i < 4; i++)
//		{
//			Vec2 nextIdx = { curNode.posIdx.x + direction[i].x, curNode.posIdx.y + direction[i].y };
//			int nextTileIdx = (nextIdx.y * _tileMaxCol) + nextIdx.x;
//
//			if (nextTileIdx < 0 || nextTileIdx > vTiles[0].size()) continue;
//			if (nextIdx.x < 0 || nextIdx.y < 0 || nextIdx.x > _tileMaxCol - 1 || nextIdx.y > _tileMaxRow - 1) continue;
//			if (vTiles[0][nextTileIdx]->_isSearch) continue;
//
//			int depth = abs(nextIdx.x - PLAYER->getPosIdx().x) + abs(nextIdx.y - PLAYER->getPosIdx().y);
//
//			if (depth > PLAYER->getLightPower()) break;
//
//
//			Node nextNode;
//			nextNode.posIdx = { nextIdx.x, nextIdx.y };
//			nextNode.alpha = 255 - (10 * depth);
//			nextNode.isCollider = vTiles[1][nextTileIdx]->_isCollider;
//			nextNode.tileIdx = nextTileIdx;
//
//			tileNodeQueue.push(nextNode);
//			vNodeList.push_back(nextNode);
//
//			vTiles[0][nextTileIdx]->_isSearch = true;
//
//			if (!vTiles[0][nextTileIdx]->_isLight)
//			{
//				vTiles[0][nextTileIdx]->_isLight = true;
//				vTiles[1][nextTileIdx]->_isLight = true;
//			}
//		}
//	}
//
//	for (auto iter = vTiles[0].begin(); iter != vTiles[0].end(); ++iter)
//	{
//		(*iter)->_isSearch = false;
//	}
//
//	return vNodeList;
//}

void TestScene::tileSet(vector<Tile*> vTile, TILE_TYPE tileType)
{
	for (int i = -7; i < 8; i++)
	{
		for (int j = -11; j < 12; j++)
		{
			int curIdxX = PLAYER->getPosIdx().x + j;
			int curIdxY = PLAYER->getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > _tileMaxCol - 1) continue;
			if (curIdxY < 0 || curIdxY > _tileMaxRow - 1) continue;

			int vIndex = (curIdxY * _tileMaxCol) + curIdxX;

			// 타일을 그리지 않거나 밝혀지지 않은 부분으면 continue;
			if (!vTile[vIndex]->_isExist || !vTile[vIndex]->_isLight) continue;

			switch (tileType)
			{
			case TILE_TYPE::TERRAIN:
				IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					vTile[vIndex]->_frameX,
					vTile[vIndex]->_frameY,
					vTile[vIndex]->_alpha);
				break;
			case TILE_TYPE::WALL:
				IMAGEMANAGER->findImage("wall1")->frameAlphaRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE) - 32,
					vTile[vIndex]->_frameX,
					vTile[vIndex]->_frameY,
					vTile[vIndex]->_alpha);
				break;
			case TILE_TYPE::DECO:
				break;
			}
		}
	}
}