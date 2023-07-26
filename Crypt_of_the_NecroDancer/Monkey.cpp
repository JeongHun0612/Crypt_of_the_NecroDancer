#include "Stdafx.h"
#include "Monkey.h"

HRESULT Monkey::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_isGrab = false;

	return S_OK;
}

void Monkey::release()
{
	PLAYER->setIsGrab(false);

	Enemy::release();
}

void Monkey::update()
{
	Enemy::update();

	// 머리가 있을 때 행동 패턴
	if (_stepCount == 1 && !_isGrab)
	{
		_isMove = true;
		_img.frameX = 0;

		// 4방향 탐색 후 공격 시전
		for (int i = 0; i < 4; i++)
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[i].x , _posIdx.y + _fourDirection[i].y };

			_moveInfo[i].direction = i;
			_moveInfo[i].distance = abs(_nextPosIdx.x - PLAYER->getPosIdx().x) + abs(_nextPosIdx.y - PLAYER->getPosIdx().y);

			if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y && !PLAYER->getIsInvincible())
			{
				_isMove = false;
				_isGrab = true;
				_maxHP = 4;
				_curHP = 4;
				_posIdx = _nextPosIdx;
				_img.img = _grabImg;
				_img.maxFrameX = _grabImg->getMaxFrameX();
				_frameCycle = 0.226f;
				SOUNDMANAGER->play("monkey_grab");
				PLAYER->setIsGrab(true);
				_stepCount = 0;
				break;
			}
		}

		if (!_isGrab)
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
				for (int i = 0; i < 4; i++)
				{
					_curMoveDirection = _moveInfo[i].direction;
					_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
					_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

					if (!_vStage1Wall[_nextTileIdx]->_isCollider && !_vStage1Terrain[_nextTileIdx]->_isCollider)
					{
						if (_curMoveDirection == LEFT) _img.frameY = 1;
						if (_curMoveDirection == RIGHT) _img.frameY = 3;

						_vStage1Terrain[_curTileIdx]->_isCollider = false;
						_vStage1Terrain[_nextTileIdx]->_isCollider = true;

						break;
					}
				}
			}
			else
			{
				_isMove = false;
			}
		}

		_stepCount = 0;
	}

	if (_isMove)
	{
		switch (_curMoveDirection)
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
			_jumpPower = 5.0f;
			_posIdx = _nextPosIdx;
			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			_isMove = false;
		}
	}

	if (_isHit)
	{
		SOUNDMANAGER->play("monkey_hit");
		_isHit = false;
	}
}

void Monkey::render(HDC hdc)
{
	Enemy::render(hdc);
}
