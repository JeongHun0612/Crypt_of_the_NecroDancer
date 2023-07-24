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
	// �÷��̾���� �Ÿ�
	_distance = sqrt(pow(_posIdx.x - PLAYER->getPosIdx().x, 2) + pow(_posIdx.y - PLAYER->getPosIdx().y, 2));

	// ������ Ÿ�̹�
	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount < _beatCount)
	{
		_stepCount++;
		_prevBeatCount = _beatCount;
	}

	// ������ �̹��� ����
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


	// ���� ��� ������ ����
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
	// �Ÿ��� ���� ��� ��ȭ
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
		// �׸��� ���
		_shadowImg->alphaRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 13,
			180);

		// �̹��� ���
		_img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64 + 8 + _pos.x,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 - 18 +  _pos.y,
			_img->getFrameX(),
			_img->getFrameY());


		// HP ���
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

		// ���� ���
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