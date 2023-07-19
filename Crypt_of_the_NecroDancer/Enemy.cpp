#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxX, int idxY, int maxHP, int power, int coinCount)
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

	_frameX = 0;
	_frameY = 0;

	_beatCount = 0;
	_prevBeatCount = 0;

	_isAttack = false;
	_isMove = false;

	return S_OK;
}

void Enemy::release()
{
	cout << "release" << endl;
}

void Enemy::update()
{
	// 움직임 타이밍
	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount + 1 < _beatCount)
	{
		_isMove = true;
		_prevBeatCount = _beatCount;
	}


	// 프레임 이미지 변경
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.2f)
	{
		_img->setFrameX(_frameX);

		if (_frameX == _img->getMaxFrameX())
		{
			_frameX = 0;
		}

		_frameX++;

		_count = 0.f;
	}


	// 공격 모션 프레임 변경
	if (_isAttack)
	{
		_effectCount += TIMEMANAGER->getDeltaTime();
		if (_effectCount >= 0.13f)
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

void Enemy::render(HDC hdc)
{
	// 거리에 따른 모습 변화
	int distance = sqrt(pow(_idxX - PLAYER->getPosIdxX(), 2) + pow(_idxY - PLAYER->getPosIdxY(), 2));

	if (distance > PLAYER->getLightPower())
	{
		_img->setFrameY(_frameY - 1);
	}
	else
	{
		_img->setFrameY(_frameY + 1);
	}

	// 적 개체 이미지 출력
	_img->frameRender(hdc,
		CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64,
		CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 + _posY,
		_frameX, _frameY);


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