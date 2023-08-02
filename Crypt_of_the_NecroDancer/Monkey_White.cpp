#include "Stdafx.h"
#include "Monkey_White.h"

HRESULT Monkey_White::init(int idxX, int idxY, vector<vector<Tile*>> vTiles, int maxTileCol)
{
	Monkey::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::MONKEY_WHITE;

	_img.img = IMAGEMANAGER->findImage("monkey_white");
	_img.maxFrameX = 3;
	_img.frameY = 1;

	_maxHP = 2;
	_grabMaxHP = 6;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = RND->getFromIntTo(4, 5);

	_curMoveDirection = 0;

	return S_OK;
}

void Monkey_White::release()
{
	Monkey::release();
}

void Monkey_White::update()
{
	Monkey::update();

	// ³Ë¹é hit Ãß°¡
	if (_isHit)
	{
		SOUNDMANAGER->play("monkey_hit");

		if (!_isGrab)
		{
			_curMoveDirection = (int)PLAYER->getCurDirection();
			_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
			_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

			if (!_vWallTile[_nextTileIdx]->_isCollider && !_vTerrainTile[_nextTileIdx]->_isCollider)
			{
				_vTerrainTile[_curTileIdx]->_isCollider = false;
				_vTerrainTile[_nextTileIdx]->_isCollider = true;
				_isKnockBack = true;
			}

			_stepCount = -1;
		}

		_isHit = false;
	}
}

void Monkey_White::render(HDC hdc)
{
	Monkey::render(hdc);
}
