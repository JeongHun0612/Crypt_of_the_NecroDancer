#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxX, int idxY, int maxHP, int power, int coinCount)
{
	Slime::init(idxX, idxY, maxHP, power, coinCount);
	_img = IMAGEMANAGER->findImage("slime_blue");
	_img->setFrameY(1);

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_isUp = false;

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

		if (_isUp)
		{
			if (_idxY - 1 == PLAYER->getPosIdxY() && _idxX == PLAYER->getPosIdxX())
			{
				_nextIdxY = _idxY - 1;
				_isAttack = true;
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				_isUp = !_isUp;
			}
			else
			{
				_idxY--;
			}
		}
		else
		{
			if (_idxY + 1 == PLAYER->getPosIdxY() && _idxX == PLAYER->getPosIdxX())
			{
				_nextIdxY = _idxY + 1;
				_isAttack = true;
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				_isUp = !_isUp;
			}
			else
			{
				_idxY++;
			}
		}

		_isMove = false;
	}
}

void Slime_Blue::render(HDC hdc)
{
	Slime::render(hdc);
}
