#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);

	_img = IMAGEMANAGER->findImage("slime_blue");

	_img->setFrameY(1);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextPosIdx = { idxX , idxY };

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
		if (_isUp)
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[UP].x, _posIdx.y + _fourDirection[UP].y };
		}
		else
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[DOWN].x, _posIdx.y + _fourDirection[DOWN].y };
		}

		if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
		{
			_isAttack = true;
			SOUNDMANAGER->play("slime_attack");
			PLAYER->setIsHit(true);
			PLAYER->setCurHP(PLAYER->getCurHP() - _power);
		}

		if (!_isAttack)
		{
			_posIdx.x = _nextPosIdx.x;
			_posIdx.y = _nextPosIdx.y;
		}

		_isUp = !_isUp;
		_isMove = false;
	}
}

void Slime_Blue::render(HDC hdc)
{
	Enemy::render(hdc);
}
