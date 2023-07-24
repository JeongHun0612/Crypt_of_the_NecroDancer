#include "Stdafx.h"
#include "Skeleton_Normal.h"

HRESULT Skeleton_Normal::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);

	_img = IMAGEMANAGER->findImage("skeleton_normal");

	_img->setFrameY(5);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextPosIdx = { idxX , idxY };

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 1;

	_coinCount = 5;

	return S_OK;
}

void Skeleton_Normal::release()
{
	Enemy::release();
}

void Skeleton_Normal::update()
{
	Enemy::update();

	if (_stepCount == 2)
	{
		_isMove = true;

		// 4방향 탐색 후 공격 시전
		for (int i = 0; i < 4; i++)
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[i].x , _posIdx.y + _fourDirection[i].y };

			_moveInfo[i].direction = i;
			_moveInfo[i].distance = abs(_nextPosIdx.x - PLAYER->getPosIdx().x) + abs(_nextPosIdx.y - PLAYER->getPosIdx().y);

			if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
			{
				_isMove = false;
				_isAttack = true;
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				_stepCount = 0;
				break;
			}
		}

		// 거리 오름차순 정렬 (가까운 순)
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3 - i; ++j)
			{
				if (_moveInfo[j].distance > _moveInfo[j + 1].distance)
				{
					MoveInfo tempMoveInfo;
					tempMoveInfo = _moveInfo[j];
					_moveInfo[j] = _moveInfo[j + 1];
					_moveInfo[j + 1] = tempMoveInfo;

				}
			}
		}

		// 최소 거리가 5보다 멀고 이동 방향에 충돌체가 있을 경우 움직이지 않는다.
		if (_moveInfo[0].distance <= 5)
		{
			for (int i = 0; i < 4; i++)
			{
				_nextPosIdx = { _posIdx.x + _fourDirection[_moveInfo[i].direction].x , _posIdx.y + _fourDirection[_moveInfo[i].direction].y };
				int _nextIdx = MAX_STAGE1_COL * _nextPosIdx.y + _nextPosIdx.x;

				_moveDirection = _moveInfo[i].direction;
				if (!_vStage1Wall[_nextIdx]->_isCollider) break;
			}
		}
		else
		{
			_isMove = false;
		}

		_stepCount = 0;
	}

	if (_isMove)
	{
		switch (_moveDirection)
		{
		case LEFT:
			_pos.x -= 8.0f;
			break;
		case RIGHT:
			_pos.x += 8.0f;
			break;
		case UP:
			_pos.y -= 8.0f;
			break;
		case DOWN:
			_pos.y += 8.0f;
			break;
		}

		_pos.y -= _jumpPower;

		_jumpPower -= 1.0f;

		if (_pos.x >= 64.0f || _pos.x <= -64.0f || _pos.y >= 64.0f || _pos.y <= -64.0f)
		{
			_pos = { 0.0f, 0.0f };
			_posIdx = _nextPosIdx;
			_jumpPower = 5.0f;
			_isMove = false;
		}
	}
}

void Skeleton_Normal::render(HDC hdc)
{
	Enemy::render(hdc);
}