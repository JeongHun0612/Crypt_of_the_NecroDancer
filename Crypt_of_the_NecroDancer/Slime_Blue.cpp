#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);

	_img = IMAGEMANAGER->findImage("slime_blue");

	_img->setFrameY(1);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextIdxX = idxX;
	_nextIdxY = idxY;

	_maxHP = 2;
	_curHP = _maxHP;

	_power = 1;

	_coinCount = 5;

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
			if (_idxX == PLAYER->getNextIdxX() &&_idxY + direction[i].y == PLAYER->getNextIdxY())
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
