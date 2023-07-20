#include "Stdafx.h"
#include "Skeleton_Black.h"

HRESULT Skeleton_Black::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);
	_img = IMAGEMANAGER->findImage("skeleton_black");

	_img->setFrameY(5);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX() - 1;

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_maxHP = 3;
	_curHP = _maxHP;

	_power = 2;

	_coinCount = 6;

	return S_OK;
}

void Skeleton_Black::release()
{
	Enemy::release();
}

void Skeleton_Black::update()
{
	Enemy::update();
}

void Skeleton_Black::render(HDC hdc)
{
	Enemy::render(hdc);
}
