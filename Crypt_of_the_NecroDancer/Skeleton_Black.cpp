#include "Stdafx.h"
#include "Skeleton_Black.h"

HRESULT Skeleton_Black::init(int idxX, int idxY)
{
	Skeleton::init(idxX, idxY);

	_img.img = IMAGEMANAGER->findImage("skeleton_black");
	_img.maxFrameX = _img.img->getMaxFrameX() - 1;
	_img.frameY = 5;

	_maxHP = 3;
	_curHP = _maxHP;

	_power = 2;

	_coinCount = RND->getFromIntTo(4, 6);

	return S_OK;
}

void Skeleton_Black::release()
{
	Skeleton::release();
}

void Skeleton_Black::update()
{
	//Skeleton::update();

	if (_curHP == 1)
	{
		_img.frameY = 0;
		_img.frameX = 8;
	}
}

void Skeleton_Black::render(HDC hdc)
{
	Skeleton::render(hdc);
}
