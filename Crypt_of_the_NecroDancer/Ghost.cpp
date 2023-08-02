#include "Stdafx.h"
#include "Ghost.h"

HRESULT Ghost::init(int idxX, int idxY, vector<vector<Tile*>> vTiles, int maxTileCol)
{
	Enemy::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::GHOST;

	_img.img = IMAGEMANAGER->findImage("ghost");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 1;

	_alpha = 80;

	_coinCount = RND->getFromIntTo(2, 4);

	_isLeft = true;

	_curMoveDirection = 0;

	return S_OK;
}

void Ghost::release()
{
	SOUNDMANAGER->play("ghost_death");
	Enemy::release();
}

void Ghost::update()
{
	Enemy::update();

	if (_stepCount == 1)
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

				// 고스트와 플레이어가 서로 다른 방향을 보고 있을 경우
				if ((_curMoveDirection == LEFT && PLAYER->getCurDirection() == PLAYER_DIRECTION::RIGHT) ||
					(_curMoveDirection == RIGHT && PLAYER->getCurDirection() == PLAYER_DIRECTION::LEFT) ||
					(_curMoveDirection == UP && PLAYER->getCurDirection() == PLAYER_DIRECTION::DOWN) ||
					(_curMoveDirection == DOWN && PLAYER->getCurDirection() == PLAYER_DIRECTION::UP))
				{
					_alpha = 80;
					_isInvincible = true;
					break;
				}

				if (!_isInvincible)
				{
					_isAttack = true;
					SOUNDMANAGER->play("ghost_attack");
					PLAYER->setIsHit(true);

					if (!PLAYER->getIsInvincible())
					{
						PLAYER->setCurHP(PLAYER->getCurHP() - _power);
					}

					_stepCount = 0;
					break;
				}
			}
		}

		if (!_isAttack)
		{
			// 거리 오름차순 정렬 (가까운 순)
			sortDistance(_moveInfo);

			// 추적 최소 거리 5
			if (_moveInfo[0].distance <= PLAYER->getLightPower() + 1)
			{
				for (int i = 0; i < 4; i++)
				{
					_curMoveDirection = _moveInfo[i].direction;
					_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
					_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

					// 고스트와 플레이어가 서로 다른 방향을 보고 있을 경우
					if ((_curMoveDirection == LEFT && PLAYER->getCurDirection() == PLAYER_DIRECTION::RIGHT) ||
						(_curMoveDirection == RIGHT && PLAYER->getCurDirection() == PLAYER_DIRECTION::LEFT) ||
						(_curMoveDirection == UP && PLAYER->getCurDirection() == PLAYER_DIRECTION::DOWN) ||
						(_curMoveDirection == DOWN && PLAYER->getCurDirection() == PLAYER_DIRECTION::UP))
					{
						_alpha = 80;
						_isMove = false;
						_isInvincible = true;
						break;
					}

					if (!_vWallTile[_nextTileIdx]->_isCollider && !_vTerrainTile[_nextTileIdx]->_isCollider)
					{
						if (_curMoveDirection == LEFT) _img.frameY = 1;
						if (_curMoveDirection == RIGHT) _img.frameY = 3;

						_vTerrainTile[_curTileIdx]->_isCollider = false;
						_vTerrainTile[_nextTileIdx]->_isCollider = true;

						_alpha = 255;
						break;
					}
				}
			}
			else
			{
				_isMove = false;
			}

			_stepCount = 0;
		}
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

		if (_pos.x >= 64.0f || _pos.x <= -64.0f || _pos.y >= 64.0f || _pos.y <= -64.0f)
		{
			_pos = { 0.0f, 0.0f };
			_posIdx = _nextPosIdx;
			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			_isMove = false;
			_isInvincible = false;
		}
	}
}

void Ghost::render(HDC hdc)
{
	Enemy::render(hdc);
}
