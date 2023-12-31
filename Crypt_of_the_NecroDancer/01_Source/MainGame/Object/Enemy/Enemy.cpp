#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	_img.frameCount = 0.0f;
	_img.frameX = 0;
	_img.startFrameX = 0;
	_img.startFrameY = 0;

	_effectImg.img = IMAGEMANAGER->findImage("enemy_effect");
	_effectImg.frameCount = 0.0f;
	_effectImg.startFrameX = 0;
	_effectImg.startFrameY = 0;
	_effectImg.frameX = 0;
	_effectImg.frameY = 0;
	_effectImg.maxFrameX = _effectImg.img->getMaxFrameX();

	_shadowImg.img = IMAGEMANAGER->findImage("shadow_standard");
	_shadowImg.alpha = 150;

	_heartImg = IMAGEMANAGER->findImage("small_heart");

	_vTiles = vTiles;
	_vTerrainTile = vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = vTiles[(int)TILE_TYPE::WALL];
	_maxTileCol = maxTileCol;

	_pos = { 0.f, 0.f };
	_posIdx = { idxX, idxY };
	_nextPosIdx = { idxX, idxY };

	_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
	_nextTileIdx = 0;
	_vTerrainTile[_curTileIdx]->_isCollider = true;

	_alpha = 255;
	_distance = 0;
	_curMoveDirection = 0;

	_stepCount = 0;
	_beatCount = 0;
	_prevBeatCount = 0;

	_jumpPower = 8.0f;
	_frameCycle = 0.13f;

	_isLeft = true;
	_isMove = false;
	_isHit = false;
	_isCry = false;
	_isAttack = false;
	_isInvincible = false;

	return S_OK;
}

void Enemy::release()
{
	_vTerrainTile[_curTileIdx]->_isCollider = false;
	_vTerrainTile[_nextTileIdx]->_isCollider = false;

	UIMANAGER->addCoin(_posIdx.x, _posIdx.y, _coinCount);

	delete(this);
}

void Enemy::update()
{
	// 플레이어와의 거리
	_distance = abs(_posIdx.x - PLAYER->getPosIdx().x) + abs(_posIdx.y - PLAYER->getPosIdx().y);
	_shadowImg.alpha = 150;

	if (_vTerrainTile[_curTileIdx]->_isLight && _distance < 17)
	{
		// 움직임 타이밍
		if (PLAYER->getCurHP() > 0)
		{
			_beatCount = BEAT->getBeatCount();

			if (_prevBeatCount < _beatCount)
			{
				_stepCount++;
				_prevBeatCount = _beatCount;
			}
		}
	}

	// 캐릭터 아래 쪽에 타일이 있을 시 그림자 숨기기
	int curBottomTileIdx = _curTileIdx + _maxTileCol;
	if (_vWallTile[curBottomTileIdx]->_idxX == _posIdx.x && _vWallTile[curBottomTileIdx]->_idxY == _posIdx.y + 1 && _vWallTile[curBottomTileIdx]->_isExist)
	{
		_shadowImg.alpha = 0;
	}

	// 프레임 이미지 변경
	_img.frameCount += TIMEMANAGER->getDeltaTime();

	if (_img.frameCount >= _frameCycle)
	{
		if (_img.frameX == _img.maxFrameX)
		{
			_img.frameX = _img.startFrameX;
		}
		else
		{
			_img.frameX++;
		}

		_img.frameCount = 0.f;
	}

	// 공격 모션 프레임 변경
	if (_isAttack)
	{
		_effectImg.frameCount += TIMEMANAGER->getDeltaTime();

		if (_effectImg.frameCount >= 0.13f)
		{
			_effectImg.img->setFrameX(_effectImg.frameX);

			if (_effectImg.frameX == _effectImg.maxFrameX)
			{
				_effectImg.frameX = 0;
				_isAttack = false;
			}
			else
			{
				_effectImg.frameX++;
			}
		}
	}

	// 피격 판정 시
	if (_isHit)
	{
		if (!_isInvincible)
		{
			_curHP -= PLAYER->getCurWeapon()->getPower();
		}
	}
}

void Enemy::render(HDC hdc)
{
	if (_vTerrainTile[_curTileIdx]->_isLight && _distance < 17)
	{
		// 거리에 따른 모습 변화
		if (_distance > PLAYER->getLightPower() - 1 && _type != ENEMY_TYPE::NECRODANCER)
		{
			_img.img->setFrameY(_img.frameY - 1);
		}
		else
		{
			_img.img->setFrameY(_img.frameY);
		}

		// 그림자 출력
		_shadowImg.img->alphaRender(hdc,
			(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _shadowImg.img->getWidth() / 2 + _pos.x,
			(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _shadowImg.img->getHeight() + 8,
			_shadowImg.alpha);

		// 이미지 출력
		if (_type == ENEMY_TYPE::GHOST)
		{
			_img.img->frameAlphaRender(hdc,
				(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2 + _pos.x,
				(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight() + _pos.y,
				_img.frameX,
				_img.img->getFrameY(),
				_alpha);
		}
		else
		{
			_img.img->frameRender(hdc,
				(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2 + _pos.x,
				(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight() + _pos.y,
				_img.frameX,
				_img.img->getFrameY());
		}


		// HP 출력
		if (_maxHP > _curHP && _curHP != 0)
		{
			int renderPosX = (_maxHP * _heartImg->getFrameWidth()) / 2;

			for (int i = 0; i < _maxHP; i++)
			{
				if (i < _maxHP - _curHP)
				{
					_heartImg->setFrameX(1);
				}
				else
				{
					_heartImg->setFrameX(0);
				}

				_heartImg->frameRender(hdc,
					(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 + (i * _heartImg->getFrameWidth()) - renderPosX + _pos.x,
					CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64 + 32 - _img.img->getFrameHeight() - 20 + _pos.y,
					_heartImg->getFrameX(),
					_heartImg->getFrameY());
			}
		}

		// 공격 모션
		if (_isAttack)
		{
			_effectImg.img->frameRender(hdc,
				CAMERA->getPos().x - (PLAYER->getPosIdx().x - _nextPosIdx.x) * 64 + 10,
				CAMERA->getPos().y - (PLAYER->getPosIdx().y - _nextPosIdx.y) * 64 - 8,
				_effectImg.img->getFrameX(),
				_effectImg.img->getFrameY());
		}
	}
}

void Enemy::sortDistance(MoveInfo* moveInfo, int num, bool ASC)
{
	// 거리 정렬
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < (num - 1) - i; ++j)
		{
			// 오름차순
			if (ASC)
			{
				if (moveInfo[j].distance > moveInfo[j + 1].distance)
				{
					MoveInfo tempMoveInfo;
					tempMoveInfo = moveInfo[j];
					moveInfo[j] = moveInfo[j + 1];
					moveInfo[j + 1] = tempMoveInfo;
				}
			}

			// 내림차순
			else
			{
				if (moveInfo[j].distance < moveInfo[j + 1].distance)
				{
					MoveInfo tempMoveInfo;
					tempMoveInfo = moveInfo[j];
					moveInfo[j] = moveInfo[j + 1];
					moveInfo[j + 1] = tempMoveInfo;
				}
			}
		}
	}
}
