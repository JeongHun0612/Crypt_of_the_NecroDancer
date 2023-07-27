#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_type = ENEMY_TYPE::SLIME_GREEN;

	_img.img = IMAGEMANAGER->findImage("slime_green");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = RND->getFromIntTo(3, 5);

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

	if (_stepCount == 1)
	{
		_isMove = true;
		_img.frameX = 0;
		_stepCount = 0;
	}


	if (_isMove)
	{
		_pos.y -= _jumpPower;

		_jumpPower -= 1.5f;

		if (_pos.y >= 0.0f)
		{
			_pos.y = 0.0f;
			_jumpPower = 8.0f;
			_isMove = false;
		}
	}

	if (_isHit)
	{
		SOUNDMANAGER->play("slime_hit");

		_isHit = false;
	}
}

void Slime_Green::render(HDC hdc)
{
	Enemy::render(hdc);
}
