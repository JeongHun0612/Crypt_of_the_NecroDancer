#include "Stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init(void)
{
	for (int i = 0; i < 2500; i++)
	{
		Tile* tile = new Tile;

		tile->imgNum = { 0, 0 };
		tile->posIdx = { i % 50, i / 50 };
		tile->isColiider = false;

		_tile.push_back(tile);
	}

	return S_OK;
}

void TestScene::release(void)
{
}

void TestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//delete(_tile[0]);

		_tile.erase(_tile.begin() + 2);
	}
}

void TestScene::render(void)
{
	for (int i = 0; i < _tile.size(); i++)
	{
		_time += TIMEMANAGER->getDeltaTime();
		IMAGEMANAGER->findImage("terrain1")->frameRender(getMemDC(), _tile[i]->posIdx.x * 64, _tile[i]->posIdx.y * 64, _tile[i]->imgNum.x, _tile[i]->imgNum.y);
	}


	cout << _time << endl;
	_time = 0.0f;
}


// 충돌체 발견 시
//if (_wallTile[_nextIdxY][_nextIdxX].isColiider && _wallTile[_nextIdxY][_nextIdxX].isExist)
//{
//	_isMove = false;

//	// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
//	if (_wallTile[_nextIdxY][_nextIdxX].hardness > PLAYER->getCurShovel()->getHardNess())
//	{
//		PLAYER->getCurShovel()->setIsDig(true);
//		SOUNDMANAGER->play("dig_fail");
//	}
//	else
//	{
//		// 벽 부수기
//		_wallTile[_nextIdxY][_nextIdxX].isExist = false;
//	}

//	_nextIdxY = PLAYER->getPosIdxY();
//	_nextIdxX = PLAYER->getPosIdxX();
//}

//for (int i = 0; i < _vTerrainTile.size(); i++)
//{
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].idxX = _vTerrainTile[i].idxX;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].idxY = _vTerrainTile[i].idxY;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].frameX = _vTerrainTile[i].frameX;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].frameY = _vTerrainTile[i].frameY;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].isColiider = _vTerrainTile[i].isColiider;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].isExist = _vTerrainTile[i].isExist;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].hardness = _vTerrainTile[i].hardness;
//	_terrainTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].terrain = TERRAIN::GROUND;
//}
//for (int i = 0; i < _vWallTile.size(); i++)
//{
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].idxX = _vWallTile[i].idxX;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].idxY = _vWallTile[i].idxY;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].frameX = _vWallTile[i].frameX;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].frameY = _vWallTile[i].frameY;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].isColiider = _vWallTile[i].isColiider;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].isExist = _vWallTile[i].isExist;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].hardness = _vWallTile[i].hardness;
//	_wallTile[i / MAX_ROBBY_COL][i % MAX_ROBBY_COL].wall = WALL::BRICK;
//}

//void LobbyScene::tileSet(Tile _tile[][MAX_ROBBY_COL], TILE_TYPE type)
//{
//	for (int i = -7; i < 8; i++)
//	{
//		for (int j = -11; j < 12; j++)
//		{
//			_time += TIMEMANAGER->getDeltaTime();
//
//			int curIdxX = PLAYER->getPosIdxX() + j;
//			int curIdxY = PLAYER->getPosIdxY() + i;
//
//			if (curIdxX < 0 || curIdxX > MAX_ROBBY_COL - 1) continue;
//			if (curIdxY < 0 || curIdxY > MAX_ROBBY_ROW - 1) continue;
//
//			if (!_tile[curIdxY][curIdxX].isExist) continue;
//
//
//			// 플레이어와 타일간의 거리
//			int distance = sqrt(pow(_tile[curIdxY][curIdxX].idxX - PLAYER->getPosIdxX(), 2) + pow(_tile[curIdxY][curIdxX].idxY - PLAYER->getPosIdxY(), 2));
//
//			// 플레이어와 타일간의 거리에 따른 알파값
//			int _alpha = getAlphaSet(distance, PLAYER->getLightPower());
//
//			if (distance < PLAYER->getLightPower() || _tile[curIdxY][curIdxX].isLight)
//			{
//				switch (type)
//				{
//				case TILE_TYPE::TERRAIN:
//					_terrainImg->frameAlphaRender(getMemDC(),
//						CAMERA->getPos().x + (j * TILESIZE),
//						CAMERA->getPos().y + (i * TILESIZE),
//						_tile[curIdxY][curIdxX].frameX,
//						_tile[curIdxY][curIdxX].frameY,
//						_alpha);
//					break;
//				case TILE_TYPE::WALL:
//					_wallImg->frameAlphaRender(getMemDC(),
//						CAMERA->getPos().x + (j * TILESIZE),
//						CAMERA->getPos().y + (i * TILESIZE),
//						_tile[curIdxY][curIdxX].frameX,
//						_tile[curIdxY][curIdxX].frameY,
//						_alpha);
//					break;
//				case TILE_TYPE::DECO:
//					break;
//				}
//
//				_tile[curIdxY][curIdxX].isLight = true;
//			}
//		}
//	}
//
//	cout << _time << endl;
//	_time = 0.f;
//}
