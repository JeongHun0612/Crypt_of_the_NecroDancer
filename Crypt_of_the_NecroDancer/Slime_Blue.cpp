#include "Stdafx.h"
#include "Slime_Blue.h"

HRESULT Slime_Blue::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_img.img = IMAGEMANAGER->findImage("slime_blue");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_maxHP = 2;
	_curHP = _maxHP;

	_power = 2;

	_coinCount = RND->getFromIntTo(3, 5);

	_curMoveDirection = 0;

	_isMove = false;

	return S_OK;
}

void Slime_Blue::release()
{
	Enemy::release();

	SOUNDMANAGER->play("slime_death");
}

void Slime_Blue::update()
{
	Enemy::update();

	if (_stepCount == 2)
	{
		_isMove = true;
		_img.frameX = 0;

		_nextPosIdx = { _posIdx.x + _movePattern[_curMoveDirection].x, _posIdx.y + _movePattern[_curMoveDirection].y };

		if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
		{
			_isMove = false;
			_isAttack = true;
			SOUNDMANAGER->play("slime_attack");
			PLAYER->setIsHit(true);
			PLAYER->setCurHP(PLAYER->getCurHP() - _power);
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
			_pos.y += 8.0f;
			break;
		}

		_pos.y -= _jumpPower;
		_jumpPower -= 1.0f;

		if (_pos.y >= 64.f || _pos.y <= -64.f)
		{
			_pos.y = 0.0f;
			_jumpPower = 5.0f;
			_posIdx = _nextPosIdx;

			_curMoveDirection++;

			if (_curMoveDirection == 2)
			{
				_curMoveDirection = 0;
			}

			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			_isMove = false;
		}
	}
}

void Slime_Blue::render(HDC hdc)
{
	Enemy::render(hdc);
}
