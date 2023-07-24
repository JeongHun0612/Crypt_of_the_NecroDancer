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

	_power = 1;

	_coinCount = RND->getFromIntTo(3, 5);

	_isMove = false;
	_isUp = false;

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

		if (_isUp)
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[UP].x, _posIdx.y + _fourDirection[UP].y };
		}
		else
		{
			_nextPosIdx = { _posIdx.x + _fourDirection[DOWN].x, _posIdx.y + _fourDirection[DOWN].y };
		}

		if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
		{
			_isMove = false;
			_isAttack = true;
			SOUNDMANAGER->play("slime_attack");
			PLAYER->setIsHit(true);
			PLAYER->setCurHP(PLAYER->getCurHP() - _power);
		}

		_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

		if (_vStage1Terrain[_nextTileIdx]->_isCollider)
		{
			_isMove = false;
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
		_pos.y += (_isUp) ? -8.f : 8.f;

		if (_pos.y >= 64.f || _pos.y <= -64.f)
		{
			_pos.y = 0.0f;
			_posIdx = _nextPosIdx;
			_isUp = !_isUp;
			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			_isMove = false;
		}
	}
}

void Slime_Blue::render(HDC hdc)
{
	Enemy::render(hdc);
}
