#include "../../../../2DFrameWork/PCH/Stdafx.h"

#include "../NormalMonster/Skeleton/Skeleton_Normal.h"
#include "../NormalMonster/Skeleton/Skeleton_Yellow.h"
#include "../NormalMonster/Skeleton/Skeleton_Black.h"
#include "../MiniBoss/Dragon/Dragon_Red.h"
#include "../MiniBoss/Minotaur/Minotaur_Normal.h"
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

	_explosionImg.img = IMAGEMANAGER->findImage("effect_big_explosion");
	_explosionImg.maxFrameX = _effectImg.img->getMaxFrameX();

	_iceBlastImg.img = IMAGEMANAGER->findImage("effect_ice_blast");
	_iceBlastImg.maxFrameX = _iceBlastImg.img->getMaxFrameX();

	_maxHP = 6;
	_curHP = _maxHP;

	_power = 4;

	_coinCount = 0;

	_curMoveDirection = 0;

	_miniBossCnt = 0;
	_moveCnt = 0;

	_isSkill = false;
	_isExplosion = false;

	return S_OK;
}

void NecroDancer::release()
{
	SOUNDMANAGER->play("necrodancer_death");

	PLAYER->setIsNextStage(true);

	// 남은 몬스터 삭제
	for (int i = 0; i < TILEMAP->getEnemyList().size(); i++)
	{
		TILEMAP->getEnemyList()[i]->setCurHP(0);
	}

	Enemy::release();
}

void NecroDancer::update()
{
	Enemy::update();

	// 네크로댄서 이동
	if (_stepCount == 2 && !_isSkill)
	{
		_moveCnt++;
		_isMove = true;

		_img.frameX = 0;

		// 8방향 탐색
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

	// 스킬 시전 모션 변경
	if (_stepCount == 1 && _moveCnt == 4)
	{
		_miniBossCnt = 0;
		_isSkill = true;

		for (int i = 0; i < TILEMAP->getEnemyList().size(); i++)
		{
			if (TILEMAP->getEnemyList()[i]->getEnemyType() == ENEMY_TYPE::DRAGON_RED || TILEMAP->getEnemyList()[i]->getEnemyType() == ENEMY_TYPE::MINOTAUR_NORMAL)
			{
				_miniBossCnt++;
			}
		}

		if (_miniBossCnt < 2)
		{
			_skillPattern = RND->getInt(3);
		}
		else
		{
			_skillPattern = RND->getFromIntTo(1, 2);
		}

		switch (_skillPattern)
		{
		case MINIBOSS_SUMMON:
			_img.frameX = 4;
			_img.startFrameX = 4;
			_img.maxFrameX = 4;
			break;
		case ICE_BLAST:
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
			// 미니 보스 소환
		case MINIBOSS_SUMMON:
		{
			_miniBossCnt++;
			SOUNDMANAGER->play("necrodancer_rise");
			switch (RND->getInt(2))
			{
			case 0:
				_summonEnemy = new Minotaur_Normal;
				break;
			case 1:
				_summonEnemy = new Dragon_Red;
				break;
			}

			int posIdxX = _centerPos.x + (_centerPos.x - _posIdx.x) / 2;
			int posIdxY = _centerPos.y + (_centerPos.y - _posIdx.y) / 2;
			_summonEnemy->init(posIdxX, posIdxY, _vTiles, _maxTileCol);
			TILEMAP->getEnemyList().push_back(_summonEnemy);
		}
		break;

		// 아이스 블라스트 스킬
		case ICE_BLAST:
			SOUNDMANAGER->play("dargon_fire");
			SOUNDMANAGER->play("necrodancer_laugh");
			_iceBlastImg.x = _posIdx.x;
			_iceBlastImg.y = _posIdx.y;
			_isIceBlast = true;

			// 아이스 블라스트 범위 내 오브젝트 검사
			for (int i = 0; i < 18; i++)
			{
				Vec2 nextPosIdx;
				nextPosIdx.x = _posIdx.x + _iceBalstRange[i].x;
				nextPosIdx.y = _posIdx.y + _iceBalstRange[i].y;

				int nextTileIdx = (TILEMAP->getTileMaxCol() * nextPosIdx.y) + nextPosIdx.x;

				// 플레이어 검사
				if (nextPosIdx.x == PLAYER->getPosIdx().x && nextPosIdx.y == PLAYER->getPosIdx().y && !PLAYER->getIsInvincible())
				{
					PLAYER->setIsIce(true);
					PLAYER->setStepCount(0);
				}
			}
			break;

			// 폭발 스킬
		case EXPLOSION:
			SOUNDMANAGER->play("bomb_explode");
			SOUNDMANAGER->play("necrodancer_laugh");
			_explosionImg.x = _posIdx.x;
			_explosionImg.y = _posIdx.y;
			_isExplosion = true;

			// 폭발 범위 내 오브젝트 검사
			for (int i = 0; i < 24; i++)
			{
				Vec2 nextPosIdx;
				nextPosIdx.x = _posIdx.x + _explosionRange[i].x;
				nextPosIdx.y = _posIdx.y + _explosionRange[i].y;

				int nextTileIdx = (TILEMAP->getTileMaxCol() * nextPosIdx.y) + nextPosIdx.x;

				// 플레이어 검사
				if (nextPosIdx.x == PLAYER->getPosIdx().x && nextPosIdx.y == PLAYER->getPosIdx().y && !PLAYER->getIsInvincible())
				{
					PLAYER->setIsHit(true);
					PLAYER->setCurHP(PLAYER->getCurHP() - _power);
				}

				// 적 객체 검사
				for (int i = 0; i < TILEMAP->getEnemyList().size(); i++)
				{
					if (TILEMAP->getEnemyList()[i]->getEnemyType() == ENEMY_TYPE::NECRODANCER) continue;

					if (nextPosIdx.x == TILEMAP->getEnemyList()[i]->getPosIdx().x && nextPosIdx.y == TILEMAP->getEnemyList()[i]->getPosIdx().y)
					{
						TILEMAP->getEnemyList()[i]->setCurHP(TILEMAP->getEnemyList()[i]->getCurHP() - _power);
						break;
					}
				}
			}

			_vTerrainTile[_curTileIdx]->_isCollider = false;
			_posIdx.x = _centerPos.x + (_centerPos.x - _posIdx.x);
			_posIdx.y = RND->getFromIntTo(7, 14);

			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			_vTerrainTile[_curTileIdx]->_isCollider = true;

			break;
		}

		_img.frameX = 0;
		_img.startFrameX = 0;
		_img.maxFrameX = 3;

		_skillPattern = 0;
		_stepCount = 0;
		_isSkill = false;
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

	if (_isHit && _curHP > 0)
	{
		SOUNDMANAGER->play("necrodancer_hurt");

		for (int i = 0; i < 2; i++)
		{
			switch (RND->getInt(3))
			{
			case 0:
				_summonEnemy = new Skeleton_Normal;
				break;
			case 1:
				_summonEnemy = new Skeleton_Yellow;
				break;
			case 2:
				_summonEnemy = new Skeleton_Black;
				break;
			}

			int posIdxX = _centerPos.x + (_centerPos.x - _posIdx.x) / 2 + i;
			int posIdxY = _centerPos.y + (_centerPos.y - _posIdx.y) / 2 + i;
			_summonEnemy->init(posIdxX, posIdxY, _vTiles, _maxTileCol);
			TILEMAP->getEnemyList().push_back(_summonEnemy);
		}

		_vTerrainTile[_curTileIdx]->_isCollider = false;
		_posIdx.x = _centerPos.x + (_centerPos.x - _posIdx.x);
		_posIdx.y = RND->getFromIntTo(7, 14);

		_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
		_vTerrainTile[_curTileIdx]->_isCollider = true;

		_img.frameX = 0;
		_img.startFrameX = 0;
		_img.maxFrameX = 3;

		_isHit = false;
		_isSkill = false;
		_moveCnt = 0;
		_stepCount = 0;
	}

	if (_isExplosion)
	{
		_explosionImg.frameCount += TIMEMANAGER->getDeltaTime();

		if (_explosionImg.frameCount >= 0.04f)
		{
			if (_explosionImg.frameX == _explosionImg.maxFrameX)
			{
				_explosionImg.frameX = 0;
				_isExplosion = false;
			}
			else
			{
				_explosionImg.frameX++;
			}

			_explosionImg.frameCount = 0.0f;
		}
	}

	if (_isIceBlast)
	{
		_iceBlastImg.frameCount += TIMEMANAGER->getDeltaTime();

		if (_iceBlastImg.frameCount >= 0.04f)
		{
			if (_iceBlastImg.frameX == _iceBlastImg.maxFrameX)
			{
				_iceBlastImg.frameX = 0;
				_isIceBlast = false;
			}
			else
			{
				_iceBlastImg.frameX++;
			}

			_iceBlastImg.frameCount = 0.0f;
		}
	}
}

void NecroDancer::render(HDC hdc)
{
	Enemy::render(hdc);

	if (_isExplosion)
	{
		_explosionImg.img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - _explosionImg.x) * 64 + 32 - _explosionImg.img->getFrameWidth() / 2,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - _explosionImg.y) * 64 + 32 - _explosionImg.img->getFrameHeight() / 2,
			_explosionImg.frameX,
			_explosionImg.img->getFrameY());
	}

	if (_isIceBlast)
	{
		_iceBlastImg.img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - (_iceBlastImg.x + 1)) * 64 + 32,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - (_iceBlastImg.y - 2)) * 64 - 32,
			_iceBlastImg.frameX,
			0);

		_iceBlastImg.img->frameRender(hdc,
			CAMERA->getPos().x - (PLAYER->getPosIdx().x - (_iceBlastImg.x - 3)) * 64 - 32,
			CAMERA->getPos().y - (PLAYER->getPosIdx().y - (_iceBlastImg.y - 2)) * 64 - 32,
			_iceBlastImg.frameX,
			1);
	}
}
