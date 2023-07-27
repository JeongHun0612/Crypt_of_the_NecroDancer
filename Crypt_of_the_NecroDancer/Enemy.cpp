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
	// 플레이어와의 거리
	_distance = abs(_posIdx.x - PLAYER->getPosIdx().x) + abs(_posIdx.y - PLAYER->getPosIdx().y);

	if (_vStage1Terrain[_curTileIdx]->_isLight && _distance < 11)
	{
		// 움직임 타이밍
		_beatCount = BEAT->getBeatCount();

		if (_prevBeatCount < _beatCount)
		{
			_stepCount++;
			_prevBeatCount = _beatCount;
		}

		// 프레임 이미지 변경
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

		// 공격 모션 프레임 변경
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

		// 피격 판정 시
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
		// 거리에 따른 모습 변화
		if (_distance > PLAYER->getLightPower() - 1)
		{
			_img.img->setFrameY(_img.frameY - 1);
		}
		else
		{
			_img.img->setFrameY(_img.frameY);
		}

		// 그림자 출력
		_shadowImg->alphaRender(hdc,
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _shadowImg->getWidth() / 2 + _pos.x,
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _shadowImg->getHeight() + 8,
			180);

		// 이미지 출력
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


		// HP 출력
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

		// 공격 모션
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
	// 거리 오름차순 정렬 (가까운 순)
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
