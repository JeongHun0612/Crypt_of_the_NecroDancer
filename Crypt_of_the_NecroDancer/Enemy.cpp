#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxY, int idxX)
{
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");
	_heartImg = IMAGEMANAGER->findImage("small_heart");
	_effectImg = IMAGEMANAGER->findImage("enemy_effect");

	_vStage1Wall = TILEMAP->getStage1Wall();

	_distance = 0;
	_attackDirection = ENEMY_DIRECTION::NONE;

	_pos = { 0.f, 0.f };
	_posIdx = { idxX, idxY };
	_nextPosIdx = { idxX, idxY };

	_maxHP = 0;
	_curHP = 0;

	_power = 0;
	_coinCount = 0;

	_prevFrameY = 0;
	_maxFramX = 0;

	_beatCount = 0;
	_prevBeatCount = 0;

	_isLeft = true;
	_isMove = false;
	_isAttack = false;

	return S_OK;
}

void Enemy::release()
{
	UIMANAGER->addCoin(_posIdx.x, _posIdx.y, _coinCount);
}

void Enemy::update()
{
	// 움직임 타이밍
	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount + 1 < _beatCount)
	{
		_isMove = true;
		_prevBeatCount = _beatCount;

		// 플레이어와의 거리
		_distance = sqrt(pow(_posIdx.x - PLAYER->getPosIdx().x, 2) + pow(_posIdx.y - PLAYER->getPosIdx().y, 2));
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

				_nextPosIdx.x =  _posIdx.x;
				_nextPosIdx.y = _posIdx.y;

				_isAttack = false;
			}

			_effectImg->setFrameX(_effectImg->getFrameX() + 1);
		}
	}

}

void Enemy::render(HDC hdc)
{
	// 거리에 따른 모습 변화
	int distance = sqrt(pow(_posIdx.x - PLAYER->getPosIdx().x, 2) + pow(_posIdx.y - PLAYER->getPosIdx().y, 2));

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
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 13,
			180);

		// 이미지 출력
		_img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 + _pos.y - 18,
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
					CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + (i * 25),
					CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 43,
					_heartImg->getFrameX(),
					_heartImg->getFrameY());
			}
		}

		// 공격 모션
		if (_isAttack)
		{
			_effectImg->frameRender(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdx().x - _nextPosIdx.x) * 64 + 10,
				CAMERA->getPos().y - (PLAYER->getPosIdx().y - _nextPosIdx.y) * 64 - 8,
				_effectImg->getFrameX(),
				_effectImg->getFrameY());
		}
	}
}