#include "Stdafx.h"
#include "Bat_Blue.h"

HRESULT Bat_Blue::init(int idxX, int idxY)
{
	Enemy::init(idxX, idxY);

	_type = ENEMY_TYPE::BAT_BLUE;

	_img.img = IMAGEMANAGER->findImage("bat_blue");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 1;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 1;

	_coinCount = RND->getFromIntTo(2, 4);

	_curMoveDirection = 0;

	return S_OK;
}

void Bat_Blue::release()
{
	Enemy::release();

	SOUNDMANAGER->play("bat_death");
}

void Bat_Blue::update()
{
	Enemy::update();

	if (_stepCount == 2)
	{
		_isMove = true;
		_img.frameX = 0;

		_curMoveDirection = RND->getInt(4);

		_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x, _posIdx.y + _fourDirection[_curMoveDirection].y };

		if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
		{
			_isMove = false;
			_isAttack = true;
			SOUNDMANAGER->play("bat_attack");
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
			_curMoveDirection = 0;
			_isMove = false;
		}
	}

	if (_isHit)
	{
		SOUNDMANAGER->play("bat_hit");
		_isHit = false;
	}
}

void Bat_Blue::render(HDC hdc)
{
	Enemy::render(hdc);
}
