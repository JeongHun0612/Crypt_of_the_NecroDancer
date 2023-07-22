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

	if (_isMove)
	{
		// 4방향 탐색 후 공격 시전
		for (int i = 0; i < 4; i++)
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[i].x , _posIdx.y + _fourDirection[i].y };

			_moveInfo[i].direction = i;
			_moveInfo[i].distance = abs(_nextPosIdx.x - PLAYER->getPosIdx().x) + abs(_nextPosIdx.y - PLAYER->getPosIdx().y);

			if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
			{
				_isAttack = true;
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				break;
			}
		}

		if (!_isAttack)
		{
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

			int _minDistance = _moveInfo[0].distance;

			// 최소 거리가 5 이하인 객체만 추적
			if (_minDistance <= 5)
			{
				for (int i = 0; i < 4; i++)
				{
					int _curDirection = _moveInfo[i].direction;

					_nextPosIdx.x = _posIdx.x + _fourDirection[_curDirection].x;
					_nextPosIdx.y = _posIdx.y + _fourDirection[_curDirection].y;

					int _nextIdx = MAX_STAGE1_COL * _nextPosIdx.y + _nextPosIdx.x;

					if (!_vStage1Wall[_nextIdx]->_isCollider)
					{
						_posIdx = _nextPosIdx;
						break;
					}
				}
			}
		}

		_nextPosIdx = _posIdx;
		_isMove = false;
	}
}

void Skeleton_Normal::render(HDC hdc)
{
	Enemy::render(hdc);
}