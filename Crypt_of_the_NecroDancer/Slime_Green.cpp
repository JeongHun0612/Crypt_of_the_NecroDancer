#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);

	_img = IMAGEMANAGER->findImage("slime_green");

	_img->setFrameY(1);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = 4;

	_jumpCount = 0;

	return S_OK;
}

void Slime_Green::release()
{
	Enemy::release();

	SOUNDMANAGER->play("slime_death");
}
	
void Slime_Green::update()
{
	Enemy::update();

	if (_isMove)
	{
		_posY += (_jumpCount < 5) ? -4 : 4;

		_jumpCount++;

		if (_jumpCount == 10)
		{
			_jumpCount = 0;
			_isMove = false;
		}
	}
}

void Slime_Green::render(HDC hdc)
{
	Enemy::render(hdc);
}
