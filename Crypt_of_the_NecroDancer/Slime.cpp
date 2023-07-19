#include "Stdafx.h"
#include "Slime.h"

HRESULT Slime::init(int idxX, int idxY, int maxHP, int power, int coinCount)
{
	_heartImg = IMAGEMANAGER->findImage("small_heart");
	_effectImg = IMAGEMANAGER->findImage("enemy_effect");
	_attackDirection = ENEMY_DIRECTION::NONE;
	_idxX = idxX;
	_idxY = idxY;
	_maxHP = maxHP;
	_curHP = maxHP;
	_power = power;
	_coinCount = coinCount;
	_posX = 0;
	_posY = 0;
	_nextIdxX = 0;
	_nextIdxY = 0;

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

	if (_isAttack)
	{
		_effectCount += TIMEMANAGER->getDeltaTime();
		if (_effectCount >= 0.2f)
		{
			if (_effectImg->getFrameX() == _effectImg->getMaxFrameX())
			{
				_effectImg->setFrameX(0);
				_isAttack = false;

				_nextIdxX = _idxX;
				_nextIdxY = _idxY;
			}

			_effectImg->setFrameX(_effectImg->getFrameX() + 1);
		}
	}
}

void Slime::render(HDC hdc)
{
	// 거리에 따른 모습 변화
	int distance = sqrt(pow(_idxX - PLAYER->getPosIdxX(), 2) + pow(_idxY - PLAYER->getPosIdxY(), 2));

	if (distance > PLAYER->getLightPower())
	{
		_img->setFrameY(0);
	}
	else
	{
		_img->setFrameY(1);
	}

	// 적 개체 이미지 출력
	_img->frameRender(hdc,
		CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64,
		CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 + _posY,
		_img->getFrameX(), _img->getFrameY());


	// 적 개체 HP 출력
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

	// 공격 모션
	if (_isAttack)
	{
		_effectImg->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdxX() - _nextIdxX) * 64 + 10,
			CAMERA->getPos().y - (PLAYER->getPosIdxY() - _nextIdxY) * 64 + 10,
			_effectImg->getFrameX(),
			_effectImg->getFrameY());
	}
}