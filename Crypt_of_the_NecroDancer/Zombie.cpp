#include "Stdafx.h"
#include "Zombie.h"

HRESULT Zombie::init(int idxX, int idxY, vector<vector<Tile*>> vTiles, int maxTileCol)
{
	Enemy::init(idxX, idxY, vTiles, maxTileCol);
	
	_type = ENEMY_TYPE::ZOMBIE;

	_img.img = IMAGEMANAGER->findImage("zombie");
	_img.maxFrameX = _img.img->getMaxFrameX();
	_img.frameY = 3;

	_maxHP = 1;
	_curHP = _maxHP;

	_power = 2;

	_coinCount = RND->getFromIntTo(2, 4);

	_curMoveDirection = 0;

	return S_OK;
}

void Zombie::release()
{
	Enemy::release();
}

void Zombie::update()
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
			PLAYER->setIsHit(true);

			if (!PLAYER->getIsInvincible())
			{
				PLAYER->setCurHP(PLAYER->getCurHP() - _power);
			}
		}

		if (!_isAttack)
		{
			_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

			if (_vWallTile[_nextTileIdx]->_isCollider || _vTerrainTile[_nextTileIdx]->_isCollider)
			{
				if (_curMoveDirection == 0)
				{
					_curMoveDirection = 1;
					_img.frameY = 1;
				}
				else
				{
					_curMoveDirection = 0;
					_img.frameY = 3;
				}
				
				_isMove = false;
			}
			else
			{
				_vTerrainTile[_curTileIdx]->_isCollider = false;
				_vTerrainTile[_nextTileIdx]->_isCollider = true;
			}
		}

		_stepCount = 0;
	}

	if (_isMove)
	{
		switch (_curMoveDirection)
		{
		case 0:
			_pos.x += 8.0f;
			break;
		case 1:
			_pos.x -= 8.0f;
			break;
		}

		_pos.y -= _jumpPower;
		_jumpPower -= 1.0f;

		if (_pos.x >= 64.f || _pos.x <= -64.f)
		{
			_pos = { 0.0f, 0.0f };
			_jumpPower = 5.0f;
			_posIdx = _nextPosIdx;

			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			_isMove = false;
		}
	}
}

void Zombie::render(HDC hdc)
{
	Enemy::render(hdc);
}
