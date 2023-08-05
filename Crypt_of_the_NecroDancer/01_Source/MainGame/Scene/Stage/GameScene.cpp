#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	_padeAlpha = 0;

	return S_OK;
}

void GameScene::release(void)
{
	_vTiles.clear();

	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		delete(*iter);
	}
}

void GameScene::update(void)
{
	// ī�޶� ������Ʈ
	CAMERA->update();

	// ��Ʈ ������Ʈ
	BEAT->update();

	// �÷��̾� ������Ʈ
	if (PLAYER->getCurHP() > 0)
	{
		PLAYER->update();
	}

	// UI ������Ʈ
	UIMANAGER->update();

	// �ֳʹ� ������Ʈ
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end();)
	{
		(*iter)->update();

		// �ֳʹ� ����
		if ((*iter)->getCurHP() <= 0)
		{
			(*iter)->release();
			delete((*iter));
			iter = _vEnemy.erase(iter);
		}
		else ++iter;
	}

	// ������ ������Ʈ
	for (auto iter = _vItem.begin(); iter != _vItem.end();)
	{
		(*iter)->update();

		if ((*iter)->getIsSale())
		{
			(*iter)->release();
			iter = _vItem.erase(iter);
		}
		else ++iter;
	}

	// �뷡 ���� �� ���� ������ ����
	if (!BEAT->getIsMusic())
	{
		if (_padeAlpha < 255)
		{
			_padeAlpha += 2;

			if (_padeAlpha == 20)
			{
				IMAGEMANAGER->findImage("trap_door")->setFrameX(1);
				SOUNDMANAGER->play("trap_door_open");
				SOUNDMANAGER->play("trap_door");
			}

			if (_padeAlpha >= 20)
			{
				PLAYER->setPos(PLAYER->getPos().x, PLAYER->getPos().y + 1.0f);
				PLAYER->setPlayerAlpha(PLAYER->getPlayerAlpha() - 15);
				PLAYER->setShadowAlpha(0);

				if (PLAYER->getPlayerAlpha() <= 0)
				{
					PLAYER->setPlayerAlpha(0);
				}
			}

			if (_padeAlpha > 255)
			{
				_padeAlpha = 255;
			}
		}
	}

	// �÷��̾� ��� ��
	if (PLAYER->getCurHP() <= 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			PLAYER->release();
			SCENEMANAGER->changeScene("lobby");
		}
	}
}

void GameScene::render(void)
{
	// Ÿ�� ���
	tileSet(_vTerrainTile, TILE_TYPE::TERRAIN);
	tileSet(_vWallTile, TILE_TYPE::WALL);

	getShowTileBFS(_vTiles, _vShowNode);

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

	// ������ ���
	for (auto iter = _vItem.begin(); iter != _vItem.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// �÷��̾� ���
	if (PLAYER->getCurHP() > 0)
	{
		PLAYER->render(getMemDC());
	}

	// ���� ���
	for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
	{
		(*iter)->render(getMemDC());
	}

	// ��Ʈ ���
	BEAT->render(getMemDC());

	// UI ���
	UIMANAGER->render(getMemDC());

	// �뷡 �� �ִϸ��̼� ���
	if (!BEAT->getIsMusic())
	{
		// �� ����
		IMAGEMANAGER->findImage("trap_door")->frameRender(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("trap_door")->getFrameWidth() / 2,
			WINSIZE_Y_HALF - IMAGEMANAGER->findImage("trap_door")->getFrameHeight() / 2,
			IMAGEMANAGER->findImage("trap_door")->getFrameX(), 0);

		// ���̵� �� / �ƿ�
		IMAGEMANAGER->findImage("fade_effect")->alphaRender(getMemDC(), _padeAlpha);

		// �뷡 �� �ؽ�Ʈ
		IMAGEMANAGER->findImage("text_songend")->render(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("text_songend")->getWidth() / 2,
			200);
	}

	// �÷��̾� ��� �� ���
	if (PLAYER->getCurHP() <= 0)
	{
		IMAGEMANAGER->findImage("text_death")->render(getMemDC(),
			WINSIZE_X_HALF - IMAGEMANAGER->findImage("text_death")->getWidth() / 2,
			WINSIZE_Y_HALF + 150);
	}

	// ����� ���
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		showTileNum(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		showTileDist(_vTerrainTile);
	}
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		HPEN myPen = (HPEN)CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);

		// �׸� �� (�ֳʹ� �浹 ����, ��Ʈ ���� ����)
		showEnemyCollider(_vTerrainTile);
		DrawRectMake(getMemDC(), BEAT->getBeatRate());

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);

		SelectObject(getMemDC(), oldPen);
		DeleteObject(myPen);
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

			int tileIdx = (curIdxY * _tileMaxCol) + curIdxX;

			// Ÿ���� �׸��� �ʰų� �������� ���� �κ����� continue;
			if (!vTile[tileIdx]->_isExist || !vTile[tileIdx]->_isLight) continue;

			switch (tileType)
			{
			case TILE_TYPE::TERRAIN:
				IMAGEMANAGER->findImage("tile_terrain")->frameAlphaRender(getMemDC(),
					CAMERA->getPos().x + (j * TILESIZE),
					CAMERA->getPos().y + (i * TILESIZE),
					vTile[tileIdx]->_frameX,
					vTile[tileIdx]->_frameY,
					vTile[tileIdx]->_alpha);
				break;
			case TILE_TYPE::WALL:
				IMAGEMANAGER->findImage("tile_wall")->frameAlphaRender(getMemDC(),
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

void GameScene::getShowTileBFS(vector<vector<Tile*>> vTiles, vector<Node>& vShowNode)
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

			if (nextTileIdx < 0 || nextTileIdx > vTiles[0].size()) continue;
			if (nextIdx.x < 0 || nextIdx.y < 0 || nextIdx.x > _tileMaxCol - 1 || nextIdx.y > _tileMaxRow - 1) continue;
			if (vTiles[0][nextTileIdx]->_isSearch) continue;

			int depth = abs(nextIdx.x - PLAYER->getPosIdx().x) + abs(nextIdx.y - PLAYER->getPosIdx().y);

			if (depth > PLAYER->getLightPower()) break;

			Node nextNode;
			nextNode.posIdx = { nextIdx.x, nextIdx.y };
			nextNode.alpha = 255 - (10 * depth);
			//nextNode.alpha = 255;
			nextNode.isCollider = vTiles[1][nextTileIdx]->_isCollider;
			nextNode.tileIdx = nextTileIdx;

			tileNodeQueue.push(nextNode);
			vShowNode.push_back(nextNode);

			vTiles[0][nextTileIdx]->_isSearch = true;

			if (!vTiles[0][nextTileIdx]->_isLight)
			{
				vTiles[0][nextTileIdx]->_isLight = true;
				vTiles[1][nextTileIdx]->_isLight = true;
			}
		}
	}

	for (auto iter = vTiles[0].begin(); iter != vTiles[0].end(); ++iter)
	{
		(*iter)->_isSearch = false;
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

			int tileIdx = curIdxY * _tileMaxCol + curIdxX;

			char strIdx[15];
			sprintf_s(strIdx, "[%d, %d]", _vTile[tileIdx]->_idxY, _vTile[tileIdx]->_idxX);

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

			//int distance = sqrt(pow(_vTile[vIndex]->_idxX - PLAYER->getPosIdx().x, 2) + pow(_vTile[vIndex]->_idxY - PLAYER->getPosIdx().y, 2));
			int distance = abs(_vTile[vIndex]->_idxX - PLAYER->getPosIdx().x) + abs(_vTile[vIndex]->_idxY - PLAYER->getPosIdx().y);

			char strDist[15];
			sprintf_s(strDist, "%d", distance);
			TextOut(getMemDC(), CAMERA->getPos().x + (j * TILESIZE), CAMERA->getPos().y + (i * TILESIZE) - 32, strDist, strlen(strDist));
		}
	}
}

void GameScene::showEnemyCollider(vector<Tile*> _vTile)
{
	for (auto iter = _vTile.begin(); iter != _vTile.end(); ++iter)
	{
		if ((*iter)->_isCollider)
		{
			// ���� �浹ü ����
			RectangleMake(getMemDC(),
				CAMERA->getPos().x - (PLAYER->getPosIdx().x - (*iter)->_idxX) * 64,
				CAMERA->getPos().y - (PLAYER->getPosIdx().y - (*iter)->_idxY) * 64,
				64, 64);
		}
	}
}
