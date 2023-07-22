#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);

	_img = IMAGEMANAGER->findImage("slime_green");

	_img->setFrameY(1);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextPosIdx = { idxX , idxY };

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = 4;

	_jumpPower = 5.0f;

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
		_pos.y -= _jumpPower;

		_jumpPower -= 1.0f;

		if (_pos.y <= 0.0f)
		{
			_pos.y = 0.0f;
			_jumpPower = 5.0f;
			_isMove = false;
		}
	}
}

void Slime_Green::render(HDC hdc)
{
	Enemy::render(hdc);
}
