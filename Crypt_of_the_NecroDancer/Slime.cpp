#include "Stdafx.h"
#include "Slime.h"

HRESULT Slime::init(int idxX, int idxY, int maxHP, int coinCount)
{
	_heartImg = IMAGEMANAGER->findImage("small_heart");
	_idxX = idxX;
	_idxY = idxY;
	_maxHP = maxHP;
	_curHP = maxHP;
	_coinCount = coinCount;
	_posX = 0;
	_posY = 0;

	_beatCount = 0;
	_prevBeatCount = 0;

	_isAttack = false;
	_isMove = false;

	return S_OK;
}

void Slime::release()
{
	cout << "release" << endl;
}

void Slime::update()
{
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.2f)
	{
		if (_img->getFrameX() == _img->getMaxFrameX())
		{
			_img->setFrameX(0);
		}

		_img->setFrameX(_img->getFrameX() + 1);

		_count = 0.f;
	}
}

void Slime::render(HDC hdc)
{
	int distance = sqrt(pow(_idxX - PLAYER->getPosIdxX(), 2) + pow(_idxY - PLAYER->getPosIdxY(), 2));

	if (distance > PLAYER->getLightPower())
	{
		_img->setFrameY(0);
	}
	else
	{
		_img->setFrameY(1);
	}

	_img->frameRender(hdc,
		CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64,
		CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 + _posY,
		_img->getFrameX(), _img->getFrameY());


	if (_maxHP > _curHP)
	{
		for (int i = 0; i < _maxHP; i++)
		{
			if (i < _maxHP - _curHP)
			{
				_heartImg->setFrameX(1);
			}
			else
			{
				_heartImg->setFrameX(0);
			}

			_heartImg->frameRender(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64 + (i * 25),
				CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 - 25,
				_heartImg->getFrameX(),
				_heartImg->getFrameY());
		}
	}
}