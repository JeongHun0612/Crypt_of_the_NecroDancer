#include "Stdafx.h"
#include "Skeleton_Black.h"

HRESULT Skeleton_Black::init(int idxX, int idxY, int maxHP, int power, int coinCount)
{
	Enemy::init(idxX, idxY, maxHP, power, coinCount);
	_img = IMAGEMANAGER->findImage("skeleton_black");
	_img->setFrameY(0);

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_frameY = 5;

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
