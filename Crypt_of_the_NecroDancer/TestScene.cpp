#include "Stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init()
{
	// Ÿ�� �ʱ�ȭ
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = TILEMAP->getLoobyTerrain();
	_vWallTile = TILEMAP->getLoobyWall();

	_tileMaxCol = MAX_LOBBY_COL;
	_tileMaxRow = MAX_LOBBY_ROW;

	// �÷��̾� �ʱ�ȭ
	PLAYER->init(5, 5);

	// ��Ʈ �ʱ�ȭ
	BEAT->setIsBeat(true);

	// UI �ʱ�ȭ
	UIMANAGER->init();

	// ���� �÷���
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
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	//tileSet(_vWallTile, TILE_TYPE::WALL);

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());

	// ����� ���
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_vTerrainTile);
	}
}


void TestScene::tileSet(vector<Tile*> vTile, TILE_TYPE tileType)
{
	int direction[4] = { -1, -_tileMaxCol, 1, _tileMaxCol };

	queue<int> tileIdxQueue;

	int curIdxX = PLAYER->getPosIdx().x;
	int curIdxY = PLAYER->getPosIdx().y;

	int curTileIdx = (curIdxY * _tileMaxCol) + curIdxX;

	tileIdxQueue.push(curTileIdx);
	vTile[curTileIdx]->_isLight = true;

	tileIdxQueue.push(curTileIdx);

	while (!tileIdxQueue.empty())
	{
		int curTileIdx = tileIdxQueue.front();
		tileIdxQueue.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextTileIdx = curTileIdx + direction[i];

			int distance = abs(vTile[nextTileIdx]->_idxX - PLAYER->getPosIdx().x) + abs(vTile[nextTileIdx]->_idxY - PLAYER->getPosIdx().y);

			if (nextTileIdx < 0 || nextTileIdx > vTile.size()) continue;

			if (vTile[nextTileIdx]->_isLight || !vTile[nextTileIdx]->_isExist) continue;

			if (distance > 3) break;

			IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
			CAMERA->getPos().x - (curIdxX - vTile[nextTileIdx]->_idxX) * 64,
			CAMERA->getPos().y - (curIdxY - vTile[nextTileIdx]->_idxY) * 64,
				vTile[nextTileIdx]->_frameX,
				vTile[nextTileIdx]->_frameY,
				255);

			vTile[nextTileIdx]->_isLight = true;
			tileIdxQueue.push(nextTileIdx);
		}
	}

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

	//		// Ÿ���� �׸��� �ʰڴٸ� continue
	//		if (!vTile[vIndex]->_isExist) continue;

	//		// �÷��̾�� Ÿ�ϰ��� �Ÿ�
	//		int distance = sqrt(pow(vTile[vIndex]->_idxX - PLAYER->getPosIdx().x, 2) + pow(vTile[vIndex]->_idxY - PLAYER->getPosIdx().y, 2));

	//		// �÷��̾�� Ÿ�ϰ��� �Ÿ��� ���� ���İ�
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
