#include "Stdafx.h"
#include "Dragon_Red.h"

HRESULT Dragon_Red::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_type = ENEMY_TYPE::DRAGON_RED;

	_img.img = IMAGEMANAGER->findImage("dragon_red");
	_img.maxFrameX = 3;
	_img.frameY = 3;

	_shadowImg.img = IMAGEMANAGER->findImage("shadow_large");
	_shadowImg.alpha = 150;

	_maxHP = 6;
	_curHP = _maxHP;

	_power = 6;
	_firePower = 4;

	_coinCount = RND->getFromIntTo(30, 40);

	_curMoveDirection = 0;

	return S_OK;
}

void Dragon_Red::release()
{
	Enemy::release();
}

void Dragon_Red::update()
{
	Enemy::update();

	if (_stepCount == 2)
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
				//SOUNDMANAGER->play("minotaur_attack");
				PLAYER->setIsHit(true);

				if (!PLAYER->getIsInvincible())
				{
					PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				}
				break;
			}
		}

		if (!_isAttack)
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
					_nextTileIdx = _nextPosIdx.y * _maxTileCol + _nextPosIdx.x;

					if (_vStage1Terrain[_nextTileIdx]->_isCollider || _vStage1Wall[_nextTileIdx]->_hardNess > 2) continue;

					if (_vStage1Wall[_nextTileIdx]->_isCollider)
					{
						// 벽 부수기
						//SOUNDMANAGER->play("minotaur_wallimpact");
						_vStage1Wall[_nextTileIdx]->_isCollider = false;
						_vStage1Wall[_nextTileIdx]->_isExist = false;
						_isMove = false;
						break;
					}

					// 이동
					_vStage1Terrain[_curTileIdx]->_isCollider = false;
					_vStage1Terrain[_nextTileIdx]->_isCollider = true;
					break;
				}
			}

			// 좌우 이미지 변경
			if (_curMoveDirection == LEFT) _img.frameY = 1;
			if (_curMoveDirection == RIGHT) _img.frameY = 3;
		}
		else
		{
			_isMove = false;
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
}


void Dragon_Red::render(HDC hdc)
{
	Enemy::render(hdc);
}
