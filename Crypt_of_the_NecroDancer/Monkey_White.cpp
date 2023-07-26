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
}

void Monkey_White::render(HDC hdc)
{
	Monkey::render(hdc);
}
