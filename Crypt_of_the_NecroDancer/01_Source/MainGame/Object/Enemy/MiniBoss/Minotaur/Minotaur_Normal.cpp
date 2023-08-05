#include "../../../../../2DFrameWork/PCH/Stdafx.h"
#include "Minotaur_Normal.h"

HRESULT Minotaur_Normal::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	Enemy::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::MINOTAUR_NORMAL;

	_img.img = IMAGEMANAGER->findImage("minotaur");
	_img.maxFrameX = 3;
	_img.frameY = 1;

	_shadowImg.img = IMAGEMANAGER->findImage("shadow_large");
	_shadowImg.alpha = 150;

	_maxHP = 3;
	_curHP = _maxHP;

	_power = 4;

	_coinCount = RND->getFromIntTo(25, 35);

	_curMoveDirection = 0;

	_isCharge = false;
	_isGroggy = false;
	_isCry = false;

	return S_OK;
}

void Minotaur_Normal::release()
{
	SOUNDMANAGER->play("minotaur_death");

	PLAYER->setIsNextStage(true);

	Enemy::release();
}

void Minotaur_Normal::update()
{
	Enemy::update();

	// 첫 등장 시 사운드 출력
	if (_vTerrainTile[_curTileIdx]->_isLight && _distance < PLAYER->getLightPower() + 1 && !_isCry)
	{
		SOUNDMANAGER->play("minotaur_cry");
		_isCry = true;
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
			// 거리 오름차순 정렬 (가까운 순)
			sortDistance(_moveInfo, 4, true);

			// 추적 최소 거리 5
			if (_moveInfo[0].distance <= PLAYER->getLightPower() + 1)
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

					_img.frameX = 4;
					_img.startFrameX = 4;
					_img.maxFrameX = 4;

					SOUNDMANAGER->play("minotaur_charge");
				}

				if (!_isCharge)
				{
					for (int i = 0; i < 4; i++)
					{
						_curMoveDirection = _moveInfo[i].direction;
						_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
						_nextTileIdx = _nextPosIdx.y * _maxTileCol + _nextPosIdx.x;

						if (_vTerrainTile[_nextTileIdx]->_isCollider || _vWallTile[_nextTileIdx]->_hardNess > 2) continue;

						if (_vWallTile[_nextTileIdx]->_isCollider)
						{
							// 벽 부수기
							SOUNDMANAGER->play("minotaur_wallimpact");
							_vWallTile[_nextTileIdx]->_isCollider = false;
							_vWallTile[_nextTileIdx]->_isExist = false;
							_isMove = false;
							break;
						}

						// 이동
						_vTerrainTile[_curTileIdx]->_isCollider = false;
						_vTerrainTile[_nextTileIdx]->_isCollider = true;
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
		}

		_stepCount = 0;
	}

	// 차지 상태일 때
	if (_stepCount == 1 && _isCharge)
	{
		_isMove = true;

		_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
		_nextTileIdx = _nextPosIdx.y * _maxTileCol + _nextPosIdx.x;

		if (_vWallTile[_nextTileIdx]->_isCollider || _vTerrainTile[_nextTileIdx]->_isCollider)
		{
			// 벽 부수기
			SOUNDMANAGER->play("minotaur_wallimpact");
			_isMove = false;
			_isCharge = false;
			_isGroggy = true;

			// 돌진 시 벽 강도가 3이하로만 부술 수 있다.
			if (_vWallTile[_nextTileIdx]->_hardNess <= 3)
			{
				_vWallTile[_nextTileIdx]->_isCollider = false;
				_vWallTile[_nextTileIdx]->_isExist = false;
			}
		}
		// 플레이어 공격
		else if (_nextPosIdx.x == PLAYER->getPosIdx().x && _nextPosIdx.y == PLAYER->getPosIdx().y ||
			_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
		{
			SOUNDMANAGER->play("minotaur_attack");
			PLAYER->setIsHit(true);

			if (!PLAYER->getIsInvincible())
			{
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
			}

			_isAttack = true;
			_isMove = false;
			_isCharge = false;
			_isGroggy = true;
		}
		else
		{
			// 이동
			_vTerrainTile[_curTileIdx]->_isCollider = false;
			_vTerrainTile[_nextTileIdx]->_isCollider = true;
		}

		_stepCount = 0;
	}

	// 그로기 상태일 때
	if (_stepCount == 1 && _isGroggy)
	{
		_img.frameX = 5;
		_img.startFrameX = 5;
		_img.maxFrameX = 8;
	}

	// 그로기 상태 해제
	if (_stepCount == 3 && _isGroggy)
	{
		_img.frameX = 0;
		_img.startFrameX = 0;
		_img.maxFrameX = 3;

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
