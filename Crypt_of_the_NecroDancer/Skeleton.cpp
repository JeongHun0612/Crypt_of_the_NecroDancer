#include "Stdafx.h"
#include "Skeleton.h"

HRESULT Skeleton::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_isNoHead = false;

	return S_OK;
}

void Skeleton::release()
{
	Enemy::release();
}

void Skeleton::update()
{
	Enemy::update();

	if (_stepCount == 2 && !_isNoHead)
	{
		_isMove = true;
		_img.frameX = 0;

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

			// 최소 거리가 5이하이고 이동 방향에 충돌체가 없을 경우 움직인다.
			_nextPosIdx = { _posIdx.x + _fourDirection[_moveInfo[0].direction].x , _posIdx.y + _fourDirection[_moveInfo[0].direction].y };
			_moveDirection = _moveInfo[0].direction;
			_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

			if (_moveInfo[0].distance > 5)
			{
				_isMove = false;
			}

			//if (_moveInfo[0].distance > 5 || _vStage1Wall[_nextTileIdx]->_isCollider || _vStage1Terrain[_nextTileIdx]->_isCollider)
			//{
			//	_isMove = false;
			//}
			//else
			//{
			//	_vStage1Terrain[_curTileIdx]->_isCollider = false;
			//	_vStage1Terrain[_nextTileIdx]->_isCollider = true;
			//}
		}

		_stepCount = 0;
	}

	// 머리가 없을 때 (HP가 1이 남았을 때)
	if (_stepCount == 1 && _isNoHead)
	{
		_isMove = true;
		_nextPosIdx = { _posIdx.x + _fourDirection[_moveDirection].x , _posIdx.y + _fourDirection[_moveDirection].y };
		_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

		if (_vStage1Wall[_nextTileIdx]->_isCollider || _vStage1Terrain[_nextTileIdx]->_isCollider)
		{
			_isCollider = true;
		}
		else
		{
			_vStage1Terrain[_curTileIdx]->_isCollider = false;
			_vStage1Terrain[_nextTileIdx]->_isCollider = true;
		}

		_stepCount = 0;
	}

	if (_isMove)
	{
		static int moveCount = 0;

		switch (_moveDirection)
		{
		case LEFT:
			_pos.x -= 8.0f;
			_img.frameY = 5;
			break;
		case RIGHT:
			_pos.x += 8.0f;
			_img.frameY = 7;
			break;
		case UP:
			_pos.y -= 8.0f;
			break;
		case DOWN:
			_pos.y += 8.0f;
			break;
		}


		_pos.y += (moveCount < 4) ? -10 : 10;

		//_pos.y -= _jumpPower;
		//_jumpPower -= 1.0f;

		if (moveCount == 3)
		{
			if (_vStage1Wall[_nextTileIdx]->_isCollider || _vStage1Terrain[_nextTileIdx]->_isCollider)
			{
				switch (_moveDirection)
				{
				case LEFT:
					_moveDirection = RIGHT;
					break;
				case RIGHT:
					_moveDirection = LEFT;
					break;
				case UP:
					_moveDirection = UP;
					break;
				case DOWN:
					_moveDirection = DOWN;
					break;
				}
			}
			else
			{
				_vStage1Terrain[_curTileIdx]->_isCollider = false;
				_vStage1Terrain[_nextTileIdx]->_isCollider = true;
			}
		}

		if (moveCount == 7)
		{
			_pos = { 0.0f, 0.0f };
			_posIdx = _nextPosIdx;
			_jumpPower = 4.0f;
			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			moveCount = 0;
			_isMove = false;
		}

		moveCount++;
	}

	if (_isHeadMove)
	{
		switch (_headMoveDirection)
		{
		case LEFT:
			_headImg.pos.x -= 16.0f;
			_headImg.pos.y += 4.0f;
			break;
		case RIGHT:
			_headImg.pos.x += 16.0f;
			_headImg.pos.y += 4.0f;
			break;
		case UP:
			_headImg.pos.y -= 8.0f;
			break;
		case DOWN:
			_headImg.pos.y += 16.0f;
			break;
		default:
			_headImg.alpha -= 2;
			break;
		}

		if (_headImg.pos.x >= 128.0f || _headImg.pos.x <= -128.0f || _headImg.pos.y >= 128.0f || _headImg.pos.y <= -64.0f)
		{
			_headMoveDirection = NONE;
		}

		if (_headImg.alpha <= 0)
		{
			_headImg.alpha = 0;
			_isHeadMove = false;
		}
	}
}

void Skeleton::render(HDC hdc)
{
	if (_isNoHead)
	{
		_headImg.img->alphaRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _headImg.posIdx.x) * 64 + 26 + _headImg.pos.x,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _headImg.posIdx.y) * 64 - 25 + _headImg.pos.y,
			_headImg.alpha);
	}

	Enemy::render(hdc);
}
