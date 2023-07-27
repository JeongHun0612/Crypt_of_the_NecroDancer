#include "Stdafx.h"
#include "Minotaur_Normal.h"

HRESULT Minotaur_Normal::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_type = ENEMY_TYPE::MINOTAUR_NORMAL;

	_img.img = IMAGEMANAGER->findImage("minotaur");
	_img.maxFrameX = _img.img->getMaxFrameX() - 1;
	_img.frameY = 1;

	_tempImg.img = IMAGEMANAGER->findImage("minotaur");
	_tempImg.maxFrameX = _tempImg.img->getMaxFrameX() - 1;

	_groggyImg.img = IMAGEMANAGER->findImage("minotaur_groggy");
	_groggyImg.maxFrameX = _groggyImg.img->getMaxFrameX();

	_maxHP = 3;
	_curHP = _maxHP;

	_power = 2;

	_coinCount = RND->getFromIntTo(25, 35);

	_curMoveDirection = 0;

	_isCharge = false;
	_isGroggy = false;

	return S_OK;
}

void Minotaur_Normal::release()
{
	SOUNDMANAGER->play("minotaur_death");

	Enemy::release();
}

void Minotaur_Normal::update()
{
	Enemy::update();

	// 첫 등장 시 사운드 출력
	if (!_vStage1Terrain[_curTileIdx]->_isLight)
	{
		SOUNDMANAGER->play("minotaur_cry");
	}

	if (_stepCount == 1 && !_isCharge && !_isGroggy)
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
				SOUNDMANAGER->play("minotaur_attack");
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
			_isMove = true;
			_img.frameX = 0;

			// 거리 오름차순 정렬 (가까운 순)
			sortDistance(_moveInfo);

			// 추적 최소 거리 5
			if (_moveInfo[0].distance <= 5)
			{
				// 플레이어와 같은 선상에 있으면 차지 상태로 변환
				if (_posIdx.x == PLAYER->getPosIdx().x || _posIdx.y == PLAYER->getPosIdx().y)
				{
					if (_posIdx.x > PLAYER->getPosIdx().x)
					{
						_curMoveDirection = LEFT;
					}
					if (_posIdx.x < PLAYER->getPosIdx().x)
					{
						_curMoveDirection = RIGHT;
					}
					if (_posIdx.y > PLAYER->getPosIdx().y)
					{
						_curMoveDirection = UP;
					}
					if (_posIdx.y < PLAYER->getPosIdx().y)
					{
						_curMoveDirection = DOWN;
					}

					_isCharge = true;
					_isMove = false;
					_img.frameX = _img.img->getMaxFrameX();
				}

				if (!_isCharge)
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
							SOUNDMANAGER->play("minotaur_wallimpact");
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

					// 좌우 이미지 변경
					if (_curMoveDirection == LEFT)
					{
						_img.frameY = 1;
					}

					if (_curMoveDirection == RIGHT)
					{
						_img.frameY = 3;
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

	// 차지 상태일 때
	if (_stepCount == 1 && _isCharge)
	{
		_isMove = true;

		_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
		_nextTileIdx = _nextPosIdx.y * _maxTileCol + _nextPosIdx.x;

		if (_vStage1Wall[_nextTileIdx]->_isCollider)
		{
			// 벽 부수기
			SOUNDMANAGER->play("minotaur_wallimpact");
			_vStage1Wall[_nextTileIdx]->_isCollider = false;
			_vStage1Wall[_nextTileIdx]->_isExist = false;
			_isMove = false;
			_isCharge = false;
			_isGroggy = true;
		}

		_stepCount = 0;
	}

	// 그로기 상태일 때
	if (_stepCount == 1 && _isGroggy)
	{
		_img.img = _groggyImg.img;
		_img.frameX = 0;
		_img.maxFrameX = _groggyImg.maxFrameX;
	}

	// 그로기 상태 해제
	if (_stepCount == 3 && _isGroggy)
	{
		_img.img = _tempImg.img;
		_img.frameX = 0;
		_img.maxFrameX = _tempImg.maxFrameX;
		_isGroggy = false;

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
		SOUNDMANAGER->play("minotaur_hit");
		_isHit = false;
	}
}

void Minotaur_Normal::render(HDC hdc)
{
	Enemy::render(hdc);
}
