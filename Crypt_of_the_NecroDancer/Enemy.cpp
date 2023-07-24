#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxY, int idxX)
{
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");
	_heartImg = IMAGEMANAGER->findImage("small_heart");
	_effectImg = IMAGEMANAGER->findImage("enemy_effect");

	_vStage1Wall = TILEMAP->getStage1Wall();

	_pos = { 0.f, 0.f };
	_posIdx = { idxX, idxY };
	_nextPosIdx = { idxX, idxY };

	_distance = 0;

	_stepCount = 0;
	_beatCount = 0;
	_prevBeatCount = 0;

	_jumpPower = 5.0f;
	_count = 0.0f;
	_effectCount = 0.0f;

	_isLeft = true;
	_isMove = false;
	_isAttack = false;
	_isDie = false;

	return S_OK;
}

void Enemy::release()
{
	UIMANAGER->addCoin(_posIdx.x, _posIdx.y, _coinCount);
}

void Enemy::update()
{
	// 플레이어와의 거리
	_distance = sqrt(pow(_posIdx.x - PLAYER->getPosIdx().x, 2) + pow(_posIdx.y - PLAYER->getPosIdx().y, 2));

	// 움직임 타이밍
	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount < _beatCount)
	{
		_stepCount++;
		_prevBeatCount = _beatCount;
	}

	// 프레임 이미지 변경
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.13f)
	{
		if (_img->getFrameX() == _maxFramX)
		{
			_img->setFrameX(0);
		}
		else
		{
			_img->setFrameX(_img->getFrameX() + 1);
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
			}

			_effectImg->setFrameX(_effectImg->getFrameX() + 1);
		}
	}

	if (_curHP <= 0)
	{
		_isDie = true;
	}
}

void Enemy::render(HDC hdc)
{
	// 거리에 따른 모습 변화
	if (_distance > PLAYER->getLightPower())
	{
		_img->setFrameY(_prevFrameY - 1);
	}
	else
	{
		_img->setFrameY(_prevFrameY);
	}


	if (_distance < PLAYER->getLightPower() + 2)
	{
		// 그림자 출력
		_shadowImg->alphaRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 13,
			180);

		// 이미지 출력
		_img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8 + _pos.x,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 18 +  _pos.y,
			_img->getFrameX(),
			_img->getFrameY());


		// HP 출력
		if (_maxHP > _curHP && _curHP != 0)
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
					CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + (i * 25) + _pos.x,
					CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 43 + _pos.y,
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