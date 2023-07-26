#include "Stdafx.h"
#include "Monkey_White.h"

HRESULT Monkey_White::init(int idxX, int idxY)
{
	Monkey::init(idxX, idxY);

	_img.img = IMAGEMANAGER->findImage("monkey_white");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_grabImg = IMAGEMANAGER->findImage("monkey_white_grab");

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

			_vStage1Terrain[_curTileIdx]->_isCollider = false;
			_vStage1Terrain[_nextTileIdx]->_isCollider = true;

			_stepCount = -1;
			_isKnockBack = true;
		}

		_isHit = false;
	}
}

void Monkey_White::render(HDC hdc)
{
	Monkey::render(hdc);
}
