#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxY, int idxX)
{
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");
	_heartImg = IMAGEMANAGER->findImage("small_heart");
	_effectImg = IMAGEMANAGER->findImage("enemy_effect");

	_vStage1Wall = TILEMAP->getStage1Wall();

	_attackDirection = ENEMY_DIRECTION::NONE;
	_idxX = idxX;
	_idxY = idxY;

	_maxHP = 0;
	_curHP = 0;

	_power = 0;
	_coinCount = 0;

	_posX = 0;
	_posY = 0;
	_nextIdxX = 0;
	_nextIdxY = 0;

	_prevFrameY = 0;
	_maxFramX = 0;

	_beatCount = 0;
	_prevBeatCount = 0;

	_isAttack = false;
	_isMove = false;

	return S_OK;
}

void Enemy::release()
{
	UIMANAGER->addCoin(_idxX, _idxY, _coinCount);
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
		_img->setFrameX(_img->getFrameX() + 1);

		if (_img->getFrameX() == _maxFramX)
		{
			_img->setFrameX(0);
		}

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
		_img->setFrameY(_prevFrameY - 1);
	}
	else
	{
		_img->setFrameY(_prevFrameY);
	}


	if (distance < PLAYER->getLightPower() + 2)
	{
		// 그림자 출력
		_shadowImg->alphaRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 - 13,
			180);

		// 이미지 출력
		_img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdxX() - _idxX) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 + _posY - 18,
			_img->getFrameX(),
			_img->getFrameY());


		// HP 출력
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
					CAMERA->getPos().y - (PLAYER->getPosIdxY() - _idxY) * 64 - 43,
					_heartImg->getFrameX(),
					_heartImg->getFrameY());
			}
		}

		// 공격 모션
		if (_isAttack)
		{
			_effectImg->frameRender(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdxX() - _nextIdxX) * 64 + 10,
				CAMERA->getPos().y - (PLAYER->getPosIdxY() - _nextIdxY) * 64 - 8,
				_effectImg->getFrameX(),
				_effectImg->getFrameY());
		}
	}
}