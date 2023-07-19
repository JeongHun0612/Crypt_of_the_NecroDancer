#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(int idxX, int idxY, int maxHP, int power, int coinCount)
{
	Slime::init(idxX, idxY, maxHP, power, coinCount);

	_img = IMAGEMANAGER->findImage("slime_green");
	_img->setFrameY(1);

	_nextIdxX = idxX;
	_nextIdxY = idxY;


	return S_OK;
}

void Slime_Green::release()
{
	Slime::release();
}
	
void Slime_Green::update()
{
	Slime::update();

	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount < _beatCount)
	{
		_isMove = true;
		_prevBeatCount = _beatCount;
	}

	if (_isMove)
	{
 		static int jumpCount = 0;

		_posY += (jumpCount < 4) ? -4 : 4;

		jumpCount++;

		if (jumpCount == 8)
		{
			jumpCount = 0;
			_isMove = false;
		}
	}
}

void Slime_Green::render(HDC hdc)
{
	Slime::render(hdc);
}
