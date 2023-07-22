#include "Stdafx.h"
#include "Skeleton_Normal.h"

HRESULT Skeleton_Normal::init(int idxY, int idxX)
{
	Enemy::init(idxY, idxX);
	_img = IMAGEMANAGER->findImage("skeleton_normal");

	_img->setFrameY(5);
	_prevFrameY = _img->getFrameY();
	_maxFramX = _img->getMaxFrameX();

	_nextIdxX = idxX;
	_nextIdxY = idxY;

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
		int _curIdx = MAX_STAGE1_COL * _idxY + _idxX;

		int _leftIdx = _curIdx - 1;
		int _rightIdx = _curIdx + 1;
		int _topIdx = _curIdx - MAX_STAGE1_COL;
		int _bottomIdx = _curIdx + MAX_STAGE1_COL;


		// 4방향 탐색 후 공격 시전
		for (int i = 0; i < 4; i++)
		{
			_FourDistacne[i].distance = abs(_idxX + direction[i].x - PLAYER->getPosIdxX()) + abs(_idxY + direction[i].y - PLAYER->getPosIdxY());
			_FourDistacne[i].direction = i;

			if (_idxX + direction[i].x == PLAYER->getNextIdxX() && _idxY + direction[i].y == PLAYER->getNextIdxY())
			{
				_isAttack = true;
				PLAYER->setIsHit(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);

				_nextIdxX = _idxX + direction[i].x;
				_nextIdxY = _idxY + direction[i].y;
			}
		}

		if (!_isAttack)
		{
			// 거리 오름차순 정렬 (가까운 순)
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3 - i; ++j)
				{
					if (_FourDistacne[j].distance > _FourDistacne[j + 1].distance)
					{
						Distance tempDistance;
						tempDistance = _FourDistacne[j];
						_FourDistacne[j] = _FourDistacne[j + 1];
						_FourDistacne[j + 1] = tempDistance;

					}
				}
			}

			//printf("[%d, %d, %d, %d]\n", _FourDistacne[0].direction, _FourDistacne[1].direction, _FourDistacne[2].direction, _FourDistacne[3].direction);

			int _minDistance = _FourDistacne[0].distance;

			// 최소 거리가 5 이하인 객체만 추적
			if (_minDistance <= 5)
			{
				for (int i = 0; i < 4; i++)
				{
					int _curDirection = _FourDistacne[i].direction;
					_nextIdxX = _idxX + direction[_curDirection].x;
					_nextIdxY = _idxY + direction[_curDirection].y;

					int _nextIdx = MAX_STAGE1_COL * _nextIdxY + _nextIdxX;

					if (!_vStage1Wall[_nextIdx]->_isCollider)
					{
						_idxY = _nextIdxY;
						_idxX = _nextIdxX;
						break;
					}
				}
			}
		}

		_isMove = false;
	}
}

void Skeleton_Normal::render(HDC hdc)
{
	Enemy::render(hdc);
}