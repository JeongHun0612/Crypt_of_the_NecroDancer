#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxX, int idxY, int maxHP, int power, int coinCount)
{
	Enemy::init(idxX, idxY, maxHP, power, coinCount);
	_img = IMAGEMANAGER->findImage("slime_blue");

	_img->setFrameY(1);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextIdxX = idxX;
	_nextIdxY = idxY;


	_isUp = false;

	return S_OK;
}

void Slime_Blue::release()
{
	Enemy::release();

	SOUNDMANAGER->play("slime_death");
}

void Slime_Blue::update()
{
	Enemy::update();

	if (_isMove)
	{
		for (int i = 2; i < 4; i++)
		{
			if (_idxX == PLAYER->getPosIdxX() &&_idxY + direction[i].y == PLAYER->getPosIdxY())
			{
				_isAttack = true;
				SOUNDMANAGER->play("slime_attack");
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);

				_nextIdxY = _idxY + direction[i].y;
			}
		}

		if (!_isAttack)
		{
			_isUp = !_isUp;

			_idxY = (_isUp) ? _idxY - 1 : _idxY + 1;
		}

		_isMove = false;
	}
}

void Slime_Blue::render(HDC hdc)
{
	Enemy::render(hdc);
}
