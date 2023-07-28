#include "Stdafx.h"
#include "Monkey.h"

HRESULT Monkey::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_isGrab = false;
	_isKnockBack = false;

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

	if (_stepCount == 1 && !_isGrab && !_isKnockBack)
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
				_curHP = _grabMaxHP - (_maxHP - _curHP) * 3;
				_maxHP = _grabMaxHP;
				_posIdx = _nextPosIdx;
				_img.frameX = 4;
				_img.startFrameX = 4;
				_img.maxFrameX = 5;
				_frameCycle = 0.226f;
				SOUNDMANAGER->play("monkey_grab");
				PLAYER->setIsGrab(true);

				_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;
				_vStage1Terrain[_curTileIdx]->_isCollider = false;

				_stepCount = 0;
				break;
			}
		}

		if (!_isGrab)
		{
			// 거리 오름차순 정렬 (가까운 순)
			sortDistance(_moveInfo);

			// 추적 최소 거리 5보다 크면 움직이지 않는다.
			if (_moveInfo[0].distance <= PLAYER->getLightPower() + 1)
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

	if (_isMove || _isKnockBack)
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
			_isKnockBack = false;
		}
	}
}

void Monkey::render(HDC hdc)
{
	Enemy::render(hdc);
}
