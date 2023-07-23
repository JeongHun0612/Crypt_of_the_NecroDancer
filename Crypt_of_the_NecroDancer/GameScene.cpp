#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	_isLobby = false;

	_curGameScene = GAME_SCENE_TYPE::STAGE1_1;

	// Ÿ�� �ʱ�ȭ
	_vTiles = TILEMAP->getStage1Tiles();
	_vTerrainTile = TILEMAP->getStage1Terrain();
	_vWallTile = TILEMAP->getStage1Wall();

	_tileMaxCol = MAX_STAGE1_COL;
	_tileMaxRow = MAX_STAGE1_ROW;

	// �÷��̾� �ʱ�ȭ
	PLAYER->init();
	PLAYER->setTile(TILEMAP->getStage1Tiles());
	PLAYER->setTerrainTile(TILEMAP->getStage1Terrain());
	PLAYER->setWallTile(TILEMAP->getStage1Wall());
	PLAYER->setTileMaxCol(MAX_STAGE1_COL);
	PLAYER->setIsMove(false);


	// ��Ʈ �ʱ�ȭ
	BEAT->init();

	// UI �ʱ�ȭ
	UIMANAGER->init();

	// ���� ���
	SOUNDMANAGER->play("stage1-1", 0.5f);

	return S_OK;
}

void GameScene::release(void)
{

}

void GameScene::update(void)
{
	// ī�޶� ������Ʈ
	CAMERA->update();

	// ��Ʈ ������Ʈ
	BEAT->update();

	// �ֳʹ� ������Ʈ
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->update();
	}

	// �÷��̾� ������Ʈ
	PLAYER->update();


	// �ٴ� Ÿ�� Ÿ���� ����� �� �� ����
	int _nextTileIdx = (_tileMaxCol * PLAYER->getPosIdx().y) + PLAYER->getPosIdx().x;

	if (_vTerrainTile[_nextTileIdx]->_terrainType == TERRAIN_TYPE::STAIR)
	{
		switch (_curGameScene)
		{
		case GAME_SCENE_TYPE::STAGE1_1:
			SOUNDMANAGER->stop("stage1-1");
			break;
		case GAME_SCENE_TYPE::STAGE1_2:

			break;
		case GAME_SCENE_TYPE::STAGE1_BOSS:
			break;
		case GAME_SCENE_TYPE::END:
			break;
		default:
			break;
		}
	}
}

void GameScene::render(void)
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	// �÷��̾� ���
	PLAYER->render(getMemDC());

	// ���� ���
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// ��Ʈ ���
	BEAT->render(getMemDC());

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

void GameScene::tileSet(vector<Tile*> vTile, TILE_TYPE tileType)
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

			// Ÿ���� �׸��� �ʰڴٸ� continue
			if (!vTile[vIndex]->_isExist) continue;

			// �÷��̾�� Ÿ�ϰ��� �Ÿ�
			int distance = sqrt(pow(vTile[vIndex]->_idxX - PLAYER->getPosIdx().x, 2) + pow(vTile[vIndex]->_idxY - PLAYER->getPosIdx().y, 2));

			// �÷��̾�� Ÿ�ϰ��� �Ÿ��� ���� ���İ�
			int _alpha;
			_alpha = (_isLobby) ? 255 : getAlphaSet(distance, PLAYER->getLightPower());

			if (distance < PLAYER->getLightPower() || vTile[vIndex]->_isLight)
			{
				switch (tileType)
				{
				case TILE_TYPE::TERRAIN:
					IMAGEMANAGER->findImage("terrain1")->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE),
						vTile[vIndex]->_frameX,
						vTile[vIndex]->_frameY,
						_alpha);
					break;
				case TILE_TYPE::WALL:
					IMAGEMANAGER->findImage("wall1")->frameAlphaRender(getMemDC(),
						CAMERA->getPos().x + (j * TILESIZE),
						CAMERA->getPos().y + (i * TILESIZE) - 32,
						vTile[vIndex]->_frameX,
						vTile[vIndex]->_frameY,
						_alpha);
					break;
				case TILE_TYPE::DECO:
					break;
				}

				if (!vTile[vIndex]->_isLight)
				{
					vTile[vIndex]->_isLight = true;
				}
			}
		}
	}
}

void GameScene::showTileNum(vector<Tile*> _vTile)
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
			int curIdxX = PLAYER->getPosIdx().x + j;
			int curIdxY = PLAYER->getPosIdx().y + i;

			if (curIdxX < 0 || curIdxX > _tileMaxCol - 1) continue;
			if (curIdxY < 0 || curIdxY > _tileMaxRow - 1) continue;

			int vIndex = curIdxY * _tileMaxCol + curIdxX;

			int distance = sqrt(pow(_vTile[vIndex]->_idxX - PLAYER->getPosIdx().x, 2) + pow(_vTile[vIndex]->_idxY - PLAYER->getPosIdx().y, 2));

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strDist, strlen(strDist));
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