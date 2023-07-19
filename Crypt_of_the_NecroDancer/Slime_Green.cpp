#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(int idxX, int idxY, int maxHP, int power, int coinCount)
{
	Enemy::init(idxX, idxY, maxHP, power, coinCount);

	_img = IMAGEMANAGER->findImage("slime_green");

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_frameY = 1;


	return S_OK;
}

void Slime_Green::release()
{
	Enemy::release();
}
	
void Slime_Green::update()
{
	Enemy::update();

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
	Enemy::render(hdc);
}
