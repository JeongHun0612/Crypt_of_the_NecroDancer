#include "../../../../../2DFrameWork/PCH/Stdafx.h"
#include "Dragon_Red.h"

HRESULT Dragon_Red::init(int idxX, int idxY, vector<vector<Tile*>>& vTiles, int maxTileCol)
{
	Enemy::init(idxX, idxY, vTiles, maxTileCol);

	_type = ENEMY_TYPE::DRAGON_RED;

	_img.img = IMAGEMANAGER->findImage("dragon_red");
	_img.maxFrameX = 3;
	_img.frameY = 3;

	_shadowImg.img = IMAGEMANAGER->findImage("shadow_large");
	_shadowImg.alpha = 150;

	_fireImg.img = IMAGEMANAGER->findImage("dragon_fire");
	_fireImg.maxFrameX = _fireImg.img->getMaxFrameX();

	_maxHP = 6;
	_curHP = _maxHP;

	_power = 6;
	_firePower = 5;

	_coinCount = RND->getFromIntTo(30, 40);

	_curMoveDirection = 0;

	_isFire = false;
	_isPreFire = false;
	_isFireCoolDown = false;

	return S_OK;
}

void Dragon_Red::release()
{
	SOUNDMANAGER->play("dargon_death");

	PLAYER->setIsNextStage(true);

	Enemy::release();
}

void Dragon_Red::update()
{
	Enemy::update();

	// ù ���� �� ���� ���
	if (_vTerrainTile[_curTileIdx]->_isLight && _distance < PLAYER->getLightPower() + 2 && !_isCry)
	{
		SOUNDMANAGER->play("dargon_cry");
		_isCry = true;
	}

	if (_stepCount == 2 && !_isFire && !_isPreFire)
	{
		_isMove = true;
		_img.frameX = 0;

		// 4���� Ž�� �� ���� ����
		for (int i = 0; i < 4; i++)
		{
			_nextPosIdx = { _posIdx.x + _movePattern[i].x , _posIdx.y + _movePattern[i].y };

			_moveInfo[i].direction = i;
			_moveInfo[i].distance = abs(_nextPosIdx.x - PLAYER->getPosIdx().x) + abs(_nextPosIdx.y - PLAYER->getPosIdx().y);

			if (_nextPosIdx.x == PLAYER->getNextPosIdx().x && _nextPosIdx.y == PLAYER->getNextPosIdx().y)
			{
				_isMove = false;
				_isAttack = true;
				SOUNDMANAGER->play("dragon_attack");
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
			// �Ÿ� �������� ���� (����� ��)
			sortDistance(_moveInfo, 4, true);

			if (_moveInfo[0].distance <= PLAYER->getLightPower() + 2)
			{
				if (!_isPreFire)
				{
					for (int i = 0; i < 4; i++)
					{
						_curMoveDirection = _moveInfo[i].direction;
						_nextPosIdx = { _posIdx.x + _movePattern[_curMoveDirection].x , _posIdx.y + _movePattern[_curMoveDirection].y };
						_nextTileIdx = _nextPosIdx.y * _maxTileCol + _nextPosIdx.x;

						if (_vTerrainTile[_nextTileIdx]->_isCollider || _vWallTile[_nextTileIdx]->_hardNess > 2) continue;

						if (_vWallTile[_nextTileIdx]->_isCollider)
						{
							// �� �μ���
							_vWallTile[_nextTileIdx]->_isCollider = false;
							_vWallTile[_nextTileIdx]->_isExist = false;
							_isMove = false;
							break;
						}

						// �̵�
						_vTerrainTile[_curTileIdx]->_isCollider = false;
						_vTerrainTile[_nextTileIdx]->_isCollider = true;
						break;
					}

					// �÷��̾�� Y���� ������ �Ҳ� �߻� ��� ���·� ��ȯ
					if (_nextPosIdx.y == PLAYER->getPosIdx().y && abs(_posIdx.x - PLAYER->getPosIdx().x) <= 3 && !_isFireCoolDown)
					{
						_img.frameX = 4;
						_img.startFrameX = 4;
						_img.maxFrameX = 6;

						_isPreFire = true;
						SOUNDMANAGER->play("dargon_prefire");

						int tempNextTileIdx = _nextTileIdx;
						while (_fireRange < 5)
						{
							if (_posIdx.x < PLAYER->getPosIdx().x)
							{
								tempNextTileIdx++;
							}
							else
							{
								tempNextTileIdx--;
							}

							if (_vWallTile[tempNextTileIdx]->_isCollider)
							{
								break;
							}

							_fireRange++;
						}
					}
				}
			}

			// �¿� �̹��� ����
			if (_nextPosIdx.x > PLAYER->getNextPosIdx().x)
			{
				_img.frameY = 1;
			}
			else
			{
				_img.frameY = 3;
			}
		}
		else
		{
			_isMove = false;
		}

		_stepCount = 0;
		_isFireCoolDown = false;
	}

	// ȭ�� �߻� ��� ���� ������ �̹��� ����
	if (_isPreFire)
	{
		if (_img.frameX == 6)
		{
			_img.startFrameX = 6;
		}
	}

	// ȭ�� �߻� ���� ������ �̹��� ����
	if (_isFire)
	{
		if (_img.frameX == 8)
		{
			_img.startFrameX = 8;
		}

		_fireImg.frameCount++;

		if (_fireImg.frameCount > 1.5f)
		{
			if (_fireImg.frameX == _fireImg.maxFrameX)
			{
				_fireImg.frameX = 0;

				_img.frameX = 0;
				_img.startFrameX = 0;
				_img.maxFrameX = 3;

				_isFire = false;
				_isFireCoolDown = true;
				_stepCount = 0;
				_fireRange = 0;
			}
			else
			{
				_fireImg.frameX++;
			}

			_fireImg.frameCount = 0;
		}
	}

	if (_stepCount == 1 && _isPreFire)
	{
		_isPreFire = false;
		_isFire = true;
		SOUNDMANAGER->play("dargon_fire");

		_img.frameX = 7;
		_img.startFrameX = 7;
		_img.maxFrameX = 8;

		// �Ҳ� �߻� ����
		if (_posIdx.y == PLAYER->getNextPosIdx().y)
		{
			PLAYER->setIsHit(true);

			if (!PLAYER->getIsInvincible())
			{
				PLAYER->setCurHP(PLAYER->getCurHP() - _firePower);
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
		_jumpPower -= 1.0f;

		if (_pos.x >= 64.0f || _pos.x <= -64.0f || _pos.y >= 64.0f || _pos.y <= -64.0f)
		{
			_pos = { 0.0f, 0.0f };
			_jumpPower = 5.0f;
			_posIdx = _nextPosIdx;
			_curTileIdx = _maxTileCol * _posIdx.y + _posIdx.x;
			SOUNDMANAGER->play("dargon_walk");
			_isMove = false;
		}
	}

	if (_isHit)
	{
		SOUNDMANAGER->play("dargon_hit");
		_isHit = false;
	}
}


void Dragon_Red::render(HDC hdc)
{
	Enemy::render(hdc);

	_img.img->frameRender(hdc,
		(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2 + _pos.x,
		(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight() + _pos.y,
		_img.frameX,
		_img.img->getFrameY());

	if (_isFire)
	{
		for (int i = 0; i < _fireRange; i++)
		{
			// LEFT
			if (_img.frameY == 1)
			{
				_fireImg.img->frameRender(hdc,
					(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) - 64 - (i * 64),
					(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) - 16,
					_fireImg.frameX,
					_fireImg.img->getFrameY());
			}

			// RIGHT
			if (_img.frameY == 3)
			{
				_fireImg.img->frameRender(hdc,
					(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 64 + (i * 64),
					(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) - 16,
					_fireImg.frameX,
					_fireImg.img->getFrameY());
			}
		}
	}
}
