#include "Stdafx.h"
#include "Skeleton.h"

HRESULT Skeleton::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_moveCount = 0;

	_curMoveDirection = 0;

	_isCollider = false;
	_isNoHead = false;
	_isHeadMove = false;

	return S_OK;
}

void Skeleton::release()
{
	Enemy::release();

	SOUNDMANAGER->play("skeleton_death");
}

void Skeleton::update()
{
	Enemy::update();

	// 머리가 있을 때 행동 패턴
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
				SOUNDMANAGER->play("skeleton_attack");
				PLAYER->setIsHit(true);

				if (!PLAYER->getIsInvincible())
				{
					PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				}

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

			// 추적 최소 거리 5보다 크면 움직이지 않는다.
			if (_moveInfo[0].distance <= 5)
			{
				for (int i = 0; i < 3; i++)
				{
					_curMoveDirection = _moveInfo[i].direction;
					_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
					_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

					if (_vStage1Wall[_nextTileIdx]->_isCollider || _vStage1Terrain[_nextTileIdx]->_isCollider)
					{
						if (_moveInfo[i].distance == _moveInfo[i + 1].distance) continue;
						else
						{
							_isCollider = true;
							break;
						}
					}
					else
					{
						_vStage1Terrain[_curTileIdx]->_isCollider = false;
						_vStage1Terrain[_nextTileIdx]->_isCollider = true;
						break;
					}
				}

				if (_curMoveDirection == LEFT)
				{
					_img.frameY = 5;
				}

				if (_curMoveDirection == RIGHT)
				{
					_img.frameY = 7;
				}
			}
			else
			{
				_isMove = false;
			}
		}

		_stepCount = 0;
	}

	// 머리가 없을 때 행동 패턴 (HP가 1이 남았을 때)
	if (_stepCount == 1 && _isNoHead)
	{
		_isMove = true;
		_img.frameX = 8;
		_curMoveDirection = _prevMoveDirection;
		_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
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
		_moveCount++;

		switch (_curMoveDirection)
		{
		case LEFT:
			_pos.x -= (_isCollider) ? 4.0f : 8.0f;
			break;
		case RIGHT:
			_pos.x += (_isCollider) ? 4.0f : 8.0f;
			break;
		case UP:
			_pos.y -= (_isCollider) ? 4.0f : 8.0f;
			break;
		case DOWN:
			_pos.y += (_isCollider) ? 4.0f : 8.0f;
			break;
		}

		// 점프
		_pos.y -= _jumpPower;
		_jumpPower -= 1.5f;

		if (_moveCount == 4 && _isCollider)
		{
			if (_curMoveDirection % 2 == 0)
			{
				_curMoveDirection++;
			}
			else
			{
				_curMoveDirection--;
			}
		}

		if (_moveCount == 8)
		{
			_pos = { 0.0f, 0.0f };
			_jumpPower = 8.0f;
			_moveCount = 0;

			if (_isCollider)
			{
				_isCollider = false;
			}
			else
			{
				_posIdx = _nextPosIdx;
				_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			}

			_isMove = false;
		}
	}

	if (_isHeadMove)
	{
		switch (_headMoveDirection)
		{
		case LEFT:
			_headImg.pos.x -= 16.0f;
			_headImg.pos.y += 6.0f;
			break;
		case RIGHT:
			_headImg.pos.x += 16.0f;
			_headImg.pos.y += 6.0f;
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

	if (_isHit)
	{
		SOUNDMANAGER->play("skeleton_hit");
		_isHit = false;
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
