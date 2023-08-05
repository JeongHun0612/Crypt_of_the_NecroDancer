#include "../../../../2DFrameWork/PCH/Stdafx.h"

#include "NecroDancer.h"

HRESULT NecroDancer::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	Enemy::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::NECRODANCER;

	_img.img = IMAGEMANAGER->findImage("necrodancer");
	_img.maxFrameX = 3;
	_img.frameY = 0;

	_shadowImg.img = IMAGEMANAGER->findImage("shadow_large");
	_shadowImg.alpha = 150;

	_maxHP = 2;
	_curHP = _maxHP;

	_power = 0;

	_coinCount = 0;

	_curMoveDirection = 0;

	_isSkill = false;

	return S_OK;
}

void NecroDancer::release()
{
	SOUNDMANAGER->play("necrodancer_death");

	PLAYER->setIsNextStage(true);

	Enemy::release();
}

void NecroDancer::update()
{
	Enemy::update();

	if (_stepCount == 2 && !_isSkill)
	{
		_moveCnt++;
		_isMove = true;
		_img.frameX = 0;

		// 8¹æÇâ Å½»ö
		for (int i = 0; i < 8; i++)
		{
			_nextPosIdx = { _posIdx.x + _movePattern[i].x , _posIdx.y + _movePattern[i].y };

			_bossMoveInfo[i].direction = i;
			_bossMoveInfo[i].distance = abs(_nextPosIdx.x - PLAYER->getPosIdx().x) + abs(_nextPosIdx.y - PLAYER->getPosIdx().y);
		}

		if (_distance > 5)
		{
			sortDistance(_bossMoveInfo, 8, true);
		}
		else
		{
			sortDistance(_bossMoveInfo, 8, false);
		}

		for (int i = 0; i < 8; i++)
		{
			_curMoveDirection = _bossMoveInfo[i].direction;
			_nextPosIdx = { _posIdx.x + _movePattern[_curMoveDirection].x , _posIdx.y + _movePattern[_curMoveDirection].y };
			_nextTileIdx = _maxTileCol * _nextPosIdx.y + _nextPosIdx.x;

			if (!_vWallTile[_nextTileIdx]->_isCollider && !_vTerrainTile[_nextTileIdx]->_isCollider)
			{
				_vTerrainTile[_curTileIdx]->_isCollider = false;
				_vTerrainTile[_nextTileIdx]->_isCollider = true;

				break;
			}
		}

		_stepCount = 0;
	}

	if (_stepCount == 1 && _moveCnt == 4)
	{
		_isSkill = true;

		for (int i = 0; i < PLAYER->getEnemyList().size(); i++)
		{
			if (PLAYER->getEnemyList()[i]->getEnemyType() == ENEMY_TYPE::DRAGON_RED || PLAYER->getEnemyList()[i]->getEnemyType() == ENEMY_TYPE::MINOTAUR_NORMAL)
			{
				_skillPattern = RND->getFromIntTo(1, 2);
				break;
			}
		}

		if (_skillPattern == 0)
		{
			_skillPattern = RND->getInt(3);
		}

		switch (_skillPattern)
		{
		case MINIBOSS_SUMMON:
			_img.frameX = 4;
			_img.startFrameX = 4;
			_img.maxFrameX = 4;
			break;
		case ICE:
			_img.frameX = 5;
			_img.startFrameX = 5;
			_img.maxFrameX = 5;
			break;
		case EXPLOSION:
			_img.frameX = 6;
			_img.startFrameX = 6;
			_img.maxFrameX = 6;
			break;
		}

		_stepCount = 0;
		_moveCnt = 0;
	}

	if (_stepCount == 3 && _isSkill)
	{
		switch (_skillPattern)
		{
		case MINIBOSS_SUMMON:
			SOUNDMANAGER->play("necrodancer_rise");
			break;
		case ICE:
			SOUNDMANAGER->play("necrodancer_laugh");
			break;
		case EXPLOSION:
			SOUNDMANAGER->play("necrodancer_laugh");
			break;
		}
		
		_vTerrainTile[_curTileIdx]->_isCollider = false;
		_posIdx.x = _centerPos.x + (_centerPos.x - _posIdx.x);
		_posIdx.y = RND->getFromIntTo(7, 14);

		_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
		_vTerrainTile[_curTileIdx]->_isCollider = true;

		_img.frameX = 0;
		_img.startFrameX = 0;
		_img.maxFrameX = 3;

		_skillPattern = 0;
		_stepCount = 0;
	}


	if (_isMove)
	{
		switch (_curMoveDirection)
		{
		case 0:
			_pos.x -= 8.0f;
			_pos.y -= 8.0f;
			break;
		case 1:
			_pos.y -= 8.0f;
			break;
		case 2:
			_pos.x += 8.0f;
			_pos.y -= 8.0f;
			break;
		case 3:
			_pos.x += 8.0f;
			break;
		case 4:
			_pos.x += 8.0f;
			_pos.y += 8.0f;
			break;
		case 5:
			_pos.y += 8.0f;
			break;
		case 6:
			_pos.x -= 8.0f;
			_pos.y += 8.0f;
			break;
		case 7:
			_pos.x -= 8.0f;
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
			_curMoveDirection = 0;
			_isMove = false;
		}
	}

	if (_isHit)
	{
		_vTerrainTile[_curTileIdx]->_isCollider = false;
	}
}

void NecroDancer::render(HDC hdc)
{
	Enemy::render(hdc);
}
