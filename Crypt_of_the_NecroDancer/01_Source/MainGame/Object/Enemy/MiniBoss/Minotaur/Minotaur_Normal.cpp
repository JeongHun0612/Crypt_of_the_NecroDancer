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

	// ù ���� �� ���� ���
	if (_vTerrainTile[_curTileIdx]->_isLight && _distance < PLAYER->getLightPower() + 1 && !_isCry)
	{
		SOUNDMANAGER->play("minotaur_cry");
		_isCry = true;
	}

	if (_stepCount == 1 && !_isCharge && !_isGroggy)
	{
		_isMove = true;
		_img.frameX = 0;

		// 4���� Ž�� �� ���� ����
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
			// �Ÿ� �������� ���� (����� ��)
			sortDistance(_moveInfo, 4, true);

			// ���� �ּ� �Ÿ� 5
			if (_moveInfo[0].distance <= PLAYER->getLightPower() + 1)
			{
				// �÷��̾�� ���� ���� ������ ���� ���·� ��ȯ
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
							// �� �μ���
							SOUNDMANAGER->play("minotaur_wallimpact");
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
				}

				// �¿� �̹��� ����
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

	// ���� ������ ��
	if (_stepCount == 1 && _isCharge)
	{
		_isMove = true;

		_nextPosIdx = { _posIdx.x + _fourDirection[_curMoveDirection].x , _posIdx.y + _fourDirection[_curMoveDirection].y };
		_nextTileIdx = _nextPosIdx.y * _maxTileCol + _nextPosIdx.x;

		if (_vWallTile[_nextTileIdx]->_isCollider || _vTerrainTile[_nextTileIdx]->_isCollider)
		{
			// �� �μ���
			SOUNDMANAGER->play("minotaur_wallimpact");
			_isMove = false;
			_isCharge = false;
			_isGroggy = true;

			// ���� �� �� ������ 3���Ϸθ� �μ� �� �ִ�.
			if (_vWallTile[_nextTileIdx]->_hardNess <= 3)
			{
				_vWallTile[_nextTileIdx]->_isCollider = false;
				_vWallTile[_nextTileIdx]->_isExist = false;
			}
		}
		// �÷��̾� ����
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
			// �̵�
			_vTerrainTile[_curTileIdx]->_isCollider = false;
			_vTerrainTile[_nextTileIdx]->_isCollider = true;
		}

		_stepCount = 0;
	}

	// �׷α� ������ ��
	if (_stepCount == 1 && _isGroggy)
	{
		_img.frameX = 5;
		_img.startFrameX = 5;
		_img.maxFrameX = 8;
	}

	// �׷α� ���� ����
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
