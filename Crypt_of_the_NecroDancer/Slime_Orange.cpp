#include "Stdafx.h"
#include "Slime_Orange.h"

HRESULT Slime_Orange::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_img.img = IMAGEMANAGER->findImage("slime_orange");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 1;

	_coinCount = RND->getFromIntTo(3, 5);

	_curMoveDirection = 0;

	_isMove = false;

	return S_OK;
}

void Slime_Orange::release()
{
	Enemy::release();

	SOUNDMANAGER->play("slime_death");
}

void Slime_Orange::update()
{
	Enemy::update();

	if (_stepCount == 1)
	{
		_isMove = true;
		_img.frameX = 0;

		_nextPosIdx = { _posIdx.x + _movePattern[_curMoveDirection].x, _posIdx.y + _movePattern[_curMoveDirection].y };

		if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
		{
			_isMove = false;
			_isAttack = true;
			SOUNDMANAGER->play("slime_attack");

			if (!PLAYER->getIsInvincible())
			{
				PLAYER->setIsHit(true);
				PLAYER->setIsInvincible(true);
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
			}
		}

		if (!_isAttack)
		{
			_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

			if (_vStage1Wall[_nextTileIdx]->_isCollider || _vStage1Terrain[_nextTileIdx]->_isCollider)
			{
				_isMove = false;
			}
			else
			{
				_vStage1Terrain[_curTileIdx]->_isCollider = false;
				_vStage1Terrain[_nextTileIdx]->_isCollider = true;
			}
		}

		_stepCount = 0;
	}

	if (_isMove)
	{
		switch (_curMoveDirection)
		{
		case 0:
			_pos.y -= 8.0f;
			break;
		case 1:
			_pos.x += 8.0f;
			break;
		case 2:
			_pos.y += 8.0f;
			break;
		case 3:
			_pos.x -= 8.0f;
			break;
		}

		_pos.y -= _jumpPower;
		_jumpPower -= 1.5f;

		if (_pos.x >= 64.0f || _pos.x <= -64.0f || _pos.y >= 64.0f || _pos.y <= -64.0f)
		{
			_pos = { 0.0f, 0.0f };
			_jumpPower = 8.0f;
			_posIdx = _nextPosIdx;
			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;

			_curMoveDirection++;

			if (_curMoveDirection == 4)
			{
				_curMoveDirection = 0;
			}

			_isMove = false;
		}
	}

	if (_isHit)
	{
		SOUNDMANAGER->play("slime_hit");
		_isHit = false;
	}
}

void Slime_Orange::render(HDC hdc)
{
	Enemy::render(hdc);
}
