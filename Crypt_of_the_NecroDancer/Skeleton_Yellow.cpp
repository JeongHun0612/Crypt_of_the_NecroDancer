#include "Stdafx.h"
#include "Skeleton_Yellow.h"

HRESULT Skeleton_Yellow::init(int idxX, int idxY)
{
	Skeleton::init(idxX, idxY);

	_headImg.img = IMAGEMANAGER->findImage("skeleton_yellow_head");
	_headImg.pos = { 0.0f, 0.0f };
	_headImg.alpha = 255;

	_img.img = IMAGEMANAGER->findImage("skeleton_yellow");
	_img.maxFrameX = _img.img->getMaxFrameX() - 1;
	_img.frameY = 5;

	_maxHP = 2;
	_curHP = _maxHP;

	_power = 3;

	_coinCount = RND->getFromIntTo(4, 5);

	return S_OK;
}

void Skeleton_Yellow::release()
{
	Skeleton::release();
}

void Skeleton_Yellow::update()
{
	Skeleton::update();

	if (_curHP == 1 && !_isNoHead)
	{
		_isNoHead = true;
		_isHeadMove = true;

		_img.frameX = 8;
		_headImg.posIdx = _posIdx;
		_prevMoveDirection = (int)PLAYER->getCurDirection();
		_curMoveDirection = _prevMoveDirection;
		_headMoveDirection = _prevMoveDirection;
	}
}

void Skeleton_Yellow::render(HDC hdc)
{
	Skeleton::render(hdc);
}
