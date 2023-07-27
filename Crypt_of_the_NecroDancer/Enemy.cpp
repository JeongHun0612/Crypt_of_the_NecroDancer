#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxX, int idxY)
{
	_img.frameCount = 0.0f;
	_img.frameX = 0;

	_effectImg.img = IMAGEMANAGER->findImage("enemy_effect");
	_effectImg.frameCount = 0.0f;
	_effectImg.frameX = 0;
	_effectImg.frameY = 0;
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();

	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");
	_heartImg = IMAGEMANAGER->findImage("small_heart");

	_vStage1Terrain = TILEMAP->getStage1Terrain();
	_vStage1Wall = TILEMAP->getStage1Wall();
	_maxTileCol = MAX_STAGE1_COL;

	_pos = { 0.f, 0.f };
	_posIdx = { idxX, idxY };
	_nextPosIdx = { idxX, idxY };

	_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
	_nextTileIdx = 0;
	_vStage1Terrain[_curTileIdx]->_isCollider = true;

	_alpha = 255;
	_distance = 0;
	_curMoveDirection = 0;

	_stepCount = 0;
	_beatCount = 0;
	_prevBeatCount = 0;

	_jumpPower = 8.0f;
	_frameCycle = 0.13f;

	_isLeft = true;
	_isMove = false;
	_isHit = false;
	_isAttack = false;
	_isInvincible = false;

	return S_OK;
}

void Enemy::release()
{
	_vStage1Terrain[_curTileIdx]->_isCollider = false;

	UIMANAGER->addCoin(_posIdx.x, _posIdx.y, _coinCount);
}

void Enemy::update()
{
	// �÷��̾���� �Ÿ�
	_distance = abs(_posIdx.x - PLAYER->getPosIdx().x) + abs(_posIdx.y - PLAYER->getPosIdx().y);

	if (_vStage1Terrain[_curTileIdx]->_isLight && _distance < 11)
	{
		// ������ Ÿ�̹�
		_beatCount = BEAT->getBeatCount();

		if (_prevBeatCount < _beatCount)
		{
			_stepCount++;
			_prevBeatCount = _beatCount;
		}

		// ������ �̹��� ����
		_img.frameCount += TIMEMANAGER->getDeltaTime();

		if (_img.frameCount >= _frameCycle)
		{
			if (_img.frameX == _img.maxFrameX)
			{
				_img.frameX = 0;
			}
			else
			{
				_img.frameX++;
			}

			_img.frameCount = 0.f;
		}

		// ���� ��� ������ ����
		if (_isAttack)
		{
			_effectImg.frameCount += TIMEMANAGER->getDeltaTime();

			if (_effectImg.frameCount >= 0.13f)
			{
				_effectImg.img->setFrameX(_effectImg.frameX);

				if (_effectImg.frameX == _effectImg.maxFrameX)
				{
					_effectImg.frameX = 0;
					_isAttack = false;
				}
				else
				{
					_effectImg.frameX++;
				}
			}
		}

		// �ǰ� ���� ��
		if (_isHit)
		{
			if (!_isInvincible)
			{
				_curHP -= PLAYER->getCurWeapon()->getPower();
			}
		}
	}
}

void Enemy::render(HDC hdc)
{
	if (_vStage1Terrain[_curTileIdx]->_isLight && _distance < 11)
	{
		// �Ÿ��� ���� ��� ��ȭ
		if (_distance > PLAYER->getLightPower() - 1)
		{
			_img.img->setFrameY(_img.frameY - 1);
		}
		else
		{
			_img.img->setFrameY(_img.frameY);
		}

		// �׸��� ���
		_shadowImg->alphaRender(hdc,
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _shadowImg->getWidth() / 2 + _pos.x,
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _shadowImg->getHeight() + 8,
			180);

		// �̹��� ���
		if (_type == ENEMY_TYPE::GHOST)
		{
			_img.img->frameAlphaRender(hdc,
				(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2 + _pos.x,
				(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight() + _pos.y,
				_img.frameX,
				_img.img->getFrameY(),
				_alpha);
		}
		else
		{
			_img.img->frameRender(hdc,
				(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2 + _pos.x,
				(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight() + _pos.y,
				_img.frameX,
				_img.img->getFrameY());
		}


		// HP ���
		if (_maxHP > _curHP && _curHP != 0)
		{
			int renderPosX = (_maxHP * _heartImg->getFrameWidth()) / 2;

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
					(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 + (i * _heartImg->getFrameWidth()) - renderPosX + _pos.x,
					CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 + 32 - _img.img->getFrameHeight() - 20 + _pos.y,
					_heartImg->getFrameX(),
					_heartImg->getFrameY());
			}
		}

		// ���� ���
		if (_isAttack)
		{
			_effectImg.img->frameRender(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdx().x - _nextPosIdx.x) * 64 + 10,
				CAMERA->getPos().y - (PLAYER->getPosIdx().y - _nextPosIdx.y) * 64 - 8,
				_effectImg.img->getFrameX(),
				_effectImg.img->getFrameY());
		}
	}
}

void Enemy::sortDistance(MoveInfo* moveInfo)
{
	// �Ÿ� �������� ���� (����� ��)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3 - i; ++j)
		{
			if (_moveInfo[j].distance > _moveInfo[j + 1].distance)
			{
				MoveInfo tempMoveInfo;
				tempMoveInfo = moveInfo[j];
				moveInfo[j] = moveInfo[j + 1];
				moveInfo[j + 1] = tempMoveInfo;

			}
		}
	}
}
