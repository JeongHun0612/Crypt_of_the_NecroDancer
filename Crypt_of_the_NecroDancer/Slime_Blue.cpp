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

	_isMove = false;
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

	if (_stepCount == 2)
	{
		_isMove = true;

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
			_isMove = false;
			SOUNDMANAGER->play("slime_attack");
			PLAYER->setIsHit(true);
			PLAYER->setCurHP(PLAYER->getCurHP() - _power);
		}

		_stepCount = 0;
	}

	if (_isMove)
	{
		_pos.y += (_isUp) ? -8.f : 8.f;

		if (_pos.y >= 64.f || _pos.y <= -64.f)
		{
			_pos.y = 0.0f;
			_posIdx = _nextPosIdx;
			_isUp = !_isUp;
			_isMove = false;
		}
	}
}

void Slime_Blue::render(HDC hdc)
{
	Enemy::render(hdc);
}
