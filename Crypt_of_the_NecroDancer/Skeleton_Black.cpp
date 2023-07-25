#include "Stdafx.h"
#include "Skeleton_Black.h"

HRESULT Skeleton_Black::init(int idxX, int idxY)
{
	Skeleton::init(idxX, idxY);

	_headImg.img = IMAGEMANAGER->findImage("skeleton_black_head");
	_headImg.pos = { 0.0f, 0.0f };
	_headImg.alpha = 255;

	_img.img = IMAGEMANAGER->findImage("skeleton_black");
	_img.maxFrameX = _img.img->getMaxFrameX() - 1;
	_img.frameY = 5;

	_maxHP = 3;
	_curHP = _maxHP;

	_power = 4;

	_coinCount = RND->getFromIntTo(5, 6);

	return S_OK;
}

void Skeleton_Black::release()
{
	Skeleton::release();
}

void Skeleton_Black::update()
{
	Skeleton::update();

	// 머리가 없을 때 (HP가 1이 남았을 때)
	if (_stepCount == 1 && _isNoHead)
	{
		_isMove = true;
		_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
		_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;
		_curMoveDirection = _prevMoveDirection;
		_stepCount = 0;
	}
}

void Skeleton_Black::render(HDC hdc)
{
	Skeleton::render(hdc);
}
