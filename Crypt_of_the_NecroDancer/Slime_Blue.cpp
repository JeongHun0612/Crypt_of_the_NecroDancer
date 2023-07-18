#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxX, int idxY, int maxHP, int coinCount)
{
	Slime::init(idxX, idxY, maxHP, coinCount);
	_img = IMAGEMANAGER->findImage("slime_blue");
	_isUp = false;

	_img->setFrameY(1);

	return S_OK;
}

void Slime_Blue::release()
{
	Slime::release();
}

void Slime_Blue::update()
{
	Slime::update();

	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount + 1 < _beatCount)
	{
		_isMove = true;
		_prevBeatCount = _beatCount;
	}

	if (_isMove)
	{
		_isUp = !_isUp;

		_idxY = (_isUp) ? _idxY + 1 : _idxY - 1;

		_isMove = false;
	}
}

void Slime_Blue::render(HDC hdc)
{
	Slime::render(hdc);
}
