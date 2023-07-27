#include "Stdafx.h"
#include "Monkey_Normal.h"

HRESULT Monkey_Normal::init(int idxX, int idxY)
{
	Monkey::init(idxX, idxY);

	_type = ENEMY_TYPE::MONKEY_NORMAL;

	_img.img = IMAGEMANAGER->findImage("monkey_normal");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_grabImg = IMAGEMANAGER->findImage("monkey_normal_grab");

	_maxHP = 1;
	_grabMaxHP = 4;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = RND->getFromIntTo(2, 4);

	_curMoveDirection = 0;

	return S_OK;
}

void Monkey_Normal::release()
{
	Monkey::release();
}

void Monkey_Normal::update()
{
	Monkey::update();

	if (_isHit)
	{
		SOUNDMANAGER->play("monkey_hit");
		_isHit = false;
	}
}

void Monkey_Normal::render(HDC hdc)
{
	Monkey::render(hdc);
}
