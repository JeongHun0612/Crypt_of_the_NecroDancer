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

			//_distance[i] = abs(_idxX + direction[i].x - PLAYER->getPosIdxX()) + abs(_idxY + direction[i].y - PLAYER->getPosIdxY());

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
			//_minDistance = _distance[0];
			//_moveDirection = 0;

			sort(_FourDistacne, _FourDistacne + 4);
			printf("[%d, %d, %d, %d]\n", _FourDistacne[0].distance, _FourDistacne[1].distance, _FourDistacne[2].distance, _FourDistacne[2].distance);
			printf("[%d, %d, %d, %d]\n\n", _FourDistacne[0].direction, _FourDistacne[1].direction, _FourDistacne[2].direction, _FourDistacne[2].direction);


			// 최소 거리 방향 정하기
			//for (int i = 0; i < 3; i++)
			//{
			//	if (_minDistance > _distance[i + 1])
			//	{
			//		_minDistance = _distance[i + 1];
			//		_moveDirection = i + 1;
			//	}
			//}

			// 최소 거리가 5 이하인 객체만 추적
			if (_minDistance <= 5)
			{
				//printf("[%d, %d, %d, %d]\n", _distance[0], _distance[1], _distance[2], _distance[3]);
				//cout << _minDistance << endl;
				//cout << _moveDirection << endl;

				_nextIdxX = _idxX + direction[_moveDirection].x;
				_nextIdxY = _idxY + direction[_moveDirection].y;

				int _nextIdx = MAX_STAGE1_COL * _nextIdxY + _nextIdxX;

				if (_vStage1Wall[_nextIdx].getIsCollider())
				{
					for (int i = 0; i < 4; i++)
					{
						_nextIdxX = _idxX + direction[_moveDirection].x;
						_nextIdxY = _idxY + direction[_moveDirection].y;
					}
				}

				_idxX += direction[_moveDirection].x;
				_idxY += direction[_moveDirection].y;
			}
		}


		_isMove = false;
	}

	//if (abs(PLAYER->getPosIdxX() - _idxX) > abs(PLAYER->getPosIdxY() - _idxY))
	//{
	//	if (PLAYER->getPosIdxX() - _idxX > 0)
	//	{
	//		cout << "오른쪽" << endl;
	//	}
	//	else
	//	{
	//		cout << "왼쪽" << endl;
	//	}
	//}
	//else
	//{
	//	if (PLAYER->getPosIdxY() - _idxY > 0)
	//	{
	//		cout << "아래" << endl;
	//	}
	//	else
	//	{
	//		cout << "위" << endl;
	//	}
	//}
}

void Skeleton_Normal::render(HDC hdc)
{
	Enemy::render(hdc);
}
