#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "Player.h"
#include "TileMap.h"

HRESULT Player::init(int startIdxX, int startIdxY, vector<vector<Tile*>> vTiles)
{
	_vTiles = vTiles;
	_vTerrainTile = _vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = _vTiles[(int)TILE_TYPE::WALL];

	_tileMaxCol = MAX_LOBBY_COL;

	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");

	_pos = { (float)WINSIZE_X_HALF - 32.0f, (float)WINSIZE_Y_HALF - 32.0f };
	_posIdx = { startIdxX , startIdxY };
	_nextPosIdx = { startIdxX , startIdxY };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = _maxHP;

	_speed = 6.5f;
	_jumpPower = 10.0f;
	_lightPower = 6;

	_playerAlpha = 255;
	_shadowAlpha = 150;
	_effectAlpha = 50;

	_coin = 200;
	_diamond = 0;

	_isLobby = true;

	// ������ �ʱ�ȭ
	_curShovel = new Shovel;
	_curShovel->init();
	UIMANAGER->addEquipment(_curShovel);

	_curWeapon = new Weapon;
	_curWeapon->init();
	UIMANAGER->addEquipment(_curWeapon);

	_curBomb = new Bomb;
	_curBomb->init();
	UIMANAGER->addExpendable(_curBomb);

	return S_OK;
}

HRESULT Player::init(int startIdxX, int startIdxY, vector<Enemy*> vEnemy, vector<Item*> vItem, vector<vector<Tile*>> vTiles, int tileMaxCol)
{
	_vEnemy = vEnemy;
	_vItem = vItem;

	_vTiles = vTiles;
	_vTerrainTile = vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = vTiles[(int)TILE_TYPE::WALL];

	_tileMaxCol = tileMaxCol;

	_pos = { (float)WINSIZE_X_HALF - 32.0f, (float)WINSIZE_Y_HALF - 32.0f };
	_posIdx = { startIdxX , startIdxY };
	_nextPosIdx = { startIdxX , startIdxY };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_isLobby = false;
	_isLeft = false;
	_isMove = false;
	_isAttack = false;
	_isHit = false;
	_isBomb = false;
	_isInvincible = false;
	_isGrab = false;
	_isNextStage = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	// �÷��̾� ������ �̹��� ����
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.13f)
	{
		if (_headImg->getFrameX() == _headImg->getMaxFrameX())
		{
			_bodyImg->setFrameX(0);
			_headImg->setFrameX(0);
		}
		else
		{
			_headImg->setFrameX(_headImg->getFrameX() + 1);
			_bodyImg->setFrameX(_bodyImg->getFrameX() + 1);
		}

		_count = 0.0f;
	}

	// �÷��̾� Ű�Է� ����
	if (!_isMove)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_nextDirection = PLAYER_DIRECTION::LEFT;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_nextDirection = PLAYER_DIRECTION::RIGHT;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_nextDirection = PLAYER_DIRECTION::UP;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_nextDirection = PLAYER_DIRECTION::DOWN;
		}

		// ��ź ���
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (_curBomb != nullptr)
			{
				_isBomb = true;

				_curBomb->setPosIdx(_posIdx.x, _posIdx.y);

				UIMANAGER->deleteExpendable(_curBomb);
			}
		}

		// ������ ���
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (_curPotion != nullptr)
			{
				_curHP += _curPotion->getRecoveryAmount();
				if (_curHP > _maxHP)
				{
					_curHP = _maxHP;
				}

				UIMANAGER->deleteExpendable(_curPotion);
				_curPotion = nullptr;
			}
		}
	}

	int _curTileIdx = (_tileMaxCol * _posIdx.y) + _posIdx.x;

	int _curBottomTilIdx = _curTileIdx + _tileMaxCol;

	// ĳ���� �Ʒ� �ʿ� Ÿ���� ���� �� �׸��� �����
	if (_vWallTile[_curBottomTilIdx]->_idxX == _posIdx.x && _vWallTile[_curBottomTilIdx]->_idxY == _posIdx.y + 1 && _vWallTile[_curBottomTilIdx]->_isExist)
	{
		_shadowAlpha = 0;
	}

	// Ű �Է��� �ް� ���� �ൿ�� ���� ������ �������� ��
	if (_nextDirection != PLAYER_DIRECTION::NONE)
	{
		if (BEAT->getIsBeat())
		{
			_isMove = true;
			_jumpPower = 10.0f;
			_curDirection = _nextDirection;
			BEAT->setIsSuccess(true);

			if (_curDirection == PLAYER_DIRECTION::LEFT) _isLeft = true;
			if (_curDirection == PLAYER_DIRECTION::RIGHT) _isLeft = false;

			_nextPosIdx.x = _posIdx.x + _fourDirection[(int)_curDirection].x;
			_nextPosIdx.y = _posIdx.y + _fourDirection[(int)_curDirection].y;

			int _nextTileIdx = (_tileMaxCol * _nextPosIdx.y) + _nextPosIdx.x;

			if (!_isGrab)
			{
				// �� �浹ü �߰� ��
				if (_vWallTile[_nextTileIdx]->_isCollider)
				{
					_isMove = false;

					// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
					if (_vWallTile[_nextTileIdx]->_hardNess > _curShovel->getHardNess())
					{
						SOUNDMANAGER->play("dig_fail");
						addShowShovel(_nextPosIdx.x, _nextPosIdx.y);
					}
					else
					{
						// �� �μ���
						_vWallTile[_nextTileIdx]->_isExist = false;
						_vWallTile[_nextTileIdx]->_isCollider = false;
						CAMERA->setShakeCount(15);

						if (_vWallTile[_nextTileIdx]->_wallType == WALL_TYPE::DOOR)
						{
							SOUNDMANAGER->play("door_open");
						}
						else
						{
							SOUNDMANAGER->play("dig" + to_string(RND->getFromIntTo(1, 6)));
							addShowShovel(_nextPosIdx.x, _nextPosIdx.y);

							switch (_vWallTile[_nextTileIdx]->_wallType)
							{
							case WALL_TYPE::DIRT:
								SOUNDMANAGER->play("dig_dirt");
								break;
							case WALL_TYPE::BRICK:
								SOUNDMANAGER->play("dig_brick");
								break;
							case WALL_TYPE::STONE:
								SOUNDMANAGER->play("dig_stone");
								break;
							}
						}
					}
				}
			}

			// �� ��ü �˻�
			for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
			{
				if ((_isGrab && (*iter)->getPosIdx().x == _posIdx.x && (*iter)->getPosIdx().y == _posIdx.y) ||
					!_isGrab && (*iter)->getPosIdx().x == _nextPosIdx.x && (*iter)->getPosIdx().y == _nextPosIdx.y)
				{
					if ((*iter)->getIsInvincible()) continue;

					if (_isGrab)
					{
						_isAttack = false;
					}
					else
					{
						_isAttack = true;
					}

					_isMove = false;
					CAMERA->setShakeCount(25);
					SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));
					SOUNDMANAGER->play("create_hit");

					// ���� Hit ���·� �����
					(*iter)->setIsHit(true);
					break;
				}
			}

			if (!_isMove)
			{
				_nextPosIdx = _posIdx;
			}
		}
		else
		{
			BEAT->setIsMissed(true);
		}

		_nextDirection = PLAYER_DIRECTION::NONE;

		if (_isBomb && _tileMaxCol == MAX_LOBBY_COL)
		{
			_curBomb->setStepCount(_curBomb->getStepCount() + 1);
		}
	}

	// ������ �����϶�
	if (_isMove)
	{
		_pos.y -= _jumpPower;

		_jumpPower -= 2.223f;

		if (_pos.y <= 338.0f || _pos.y >= 370.0f)
		{
			_pos.y = (float)WINSIZE_Y_HALF - 32.0f;
		}
	}

	// ���� �����϶�
	for (auto iter = _vShowShovel.begin(); iter != _vShowShovel.end();)
	{
		iter->update();

		if (iter->getDestory())
		{
			iter = _vShowShovel.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// ��ź�� ������� ��
	if (_isBomb)
	{
		_curBomb->update();
	}

	// �ǰ� �����϶�
	if (_isHit)
	{
		CAMERA->setShakeCount(25);

		if (_effectAlpha == 50)
		{
			SOUNDMANAGER->play("hurt" + to_string(RND->getFromIntTo(1, 4)));
			_beatCount = BEAT->getBeatCount();
			_isInvincible = true;
		}

		_effectAlpha -= 10;

		if (_effectAlpha <= 0)
		{
			_effectAlpha = 50;
			_isHit = false;
		}

		if (_curHP <= 0)
		{
			cout << "���" << endl;
			_isHit = false;
		}
	}

	// ���� ������ ��
	if (_isInvincible)
	{
		if (_playerAlpha == 255)
		{
			_playerAlpha = 0;
		}
		else
		{
			_playerAlpha = 255;
		}

		if (_beatCount + 1 < BEAT->getBeatCount())
		{
			_beatCount = 0;
			_playerAlpha = 255;
			_isInvincible = false;
		}
	}
}

void Player::render(HDC hdc)
{
	// ���� ���
	if (_isAttack)
	{
		_curWeapon->effectRender(hdc);
	}

	// �ǰ� ���
	if (_isHit)
	{
		IMAGEMANAGER->findImage("hit_effect")->alphaRender(hdc, _effectAlpha);
	}

	// �� ���
	for (auto iter = _vShowShovel.begin(); iter != _vShowShovel.end(); ++iter)
	{
		iter->render(hdc);
	}

	// ��ź ��ġ
	if (_isBomb)
	{
		_curBomb->effectRender(hdc);
	}

	// �׸��� �̹���
	_shadowImg->alphaRender(hdc,
		_pos.x + 8,
		_pos.y - 11,
		_shadowAlpha);

	// ���� �̹���
	if (_curArmor != nullptr)
	{
		_bodyImg->frameAlphaRender(hdc,
			_pos.x + 12,
			_pos.y,
			_bodyImg->getFrameX(), (_curArmor->getType() * 2) + _isLeft,
			_playerAlpha);
	}
	else
	{
		_bodyImg->frameAlphaRender(hdc,
			_pos.x + 12,
			_pos.y,
			_bodyImg->getFrameX(), _isLeft,
			_playerAlpha);
	}

	// �Ӹ� �̹���
	_headImg->frameAlphaRender(hdc,
		_pos.x + 15,
		_pos.y - 18,
		_headImg->getFrameX(), _isLeft,
		_playerAlpha);


	// �÷��̾� ���� �ε��� ��ǥ
	char currentIdx[40];
	sprintf_s(currentIdx, "Current Index : [%d, %d]", _posIdx.y, _posIdx.x);
	TextOut(hdc, WINSIZE_X - 150, WINSIZE_Y - 40, currentIdx, strlen(currentIdx));
}

void Player::addShowShovel(int idxX, int idxY)
{
	Shovel showShovel = *_curShovel;
	showShovel.setPosIdx(idxX, idxY);

	_vShowShovel.push_back(showShovel);
}