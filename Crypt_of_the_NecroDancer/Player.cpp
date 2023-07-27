#include "Stdafx.h"
#include "Player.h"
#include "TileMap.h"

HRESULT Player::init(int startIdxX, int startIdxY)
{
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = _vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = _vTiles[(int)TILE_TYPE::WALL];

	_tileMaxCol = MAX_LOBBY_COL;

	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");

	_pos = { 0.0f, 0.0f };
	_posIdx = { startIdxX , startIdxY };
	_nextPosIdx = { startIdxX , startIdxY };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = _maxHP;

	_speed = 6.5f;
	_jumpPower = 8.0f;
	_lightPower = 5;

	_playerAlpha = 255;
	_shadowAlpha = 130;
	_effectAlpha = 50;

	_coin = 0;
	_diamond = 0;

	_isLeft = false;
	_isMove = false;
	_isAttack = false;
	_isHit = false;

	_curShovel = new Shovel;
	_curShovel->init();

	_curWeapon = new Weapon;
	_curWeapon->init(WEAPON_TYPE::DAGGER);

	_curArmor = new Armor;
	_curArmor->init();

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

		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_curArmor->setArmorType((ARMOR_TYPE)((int)_curArmor->getArmorType() + 1));
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
			_jumpPower = 8.0f;
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
					_curShovel->addShowShovel(_nextPosIdx.x, _nextPosIdx.y);

					// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
					if (_vWallTile[_nextTileIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
					{
						SOUNDMANAGER->play("dig_fail");
					}
					else
					{
						// �� �μ���
						_vWallTile[_nextTileIdx]->_isExist = false;
						_vWallTile[_nextTileIdx]->_isCollider = false;

						CAMERA->setShakeCount(15);
						SOUNDMANAGER->play("dig" + to_string(RND->getFromIntTo(1, 6)));

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

			// �� ��ü �˻�
			for (auto iter = _vEnemy.begin(); iter != _vEnemy.end(); ++iter)
			{
				if (_isGrab)
				{
					if ((*iter)->getPosIdx().x == _posIdx.x && (*iter)->getPosIdx().y == _posIdx.y)
					{
						_isMove = false;
						CAMERA->setShakeCount(30);
						SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));
						SOUNDMANAGER->play("create_hit");

						// ���� Hit ���·� ����� HP�� ���� ������ ���⸸ŭ ����
						(*iter)->setIsHit(true);
						(*iter)->setCurHP((*iter)->getCurHP() - _curWeapon->getPower());
					}
				}
				else if ((*iter)->getPosIdx().x == _nextPosIdx.x && (*iter)->getPosIdx().y == _nextPosIdx.y)
				{
					_isMove = false;
					_isAttack = true;
					CAMERA->setShakeCount(30);
					SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));
					SOUNDMANAGER->play("create_hit");

					// ���� Hit ���·� ����� HP�� ���� ������ ���⸸ŭ ����
					(*iter)->setIsHit(true);
					(*iter)->setCurHP((*iter)->getCurHP() - _curWeapon->getPower());
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
	}

	// ������ �����϶�
	if (_isMove)
	{
		switch (_curDirection)
		{
		case PLAYER_DIRECTION::LEFT:
			_pos.x -= 64 * TIMEMANAGER->getDeltaTime() * _speed;
			break;
		case PLAYER_DIRECTION::RIGHT:
			_pos.x += 64 * TIMEMANAGER->getDeltaTime() * _speed;
			break;
		case PLAYER_DIRECTION::UP:
			_pos.y -= 64 * TIMEMANAGER->getDeltaTime() * _speed;
			break;
		case PLAYER_DIRECTION::DOWN:
			_pos.y += 64 * TIMEMANAGER->getDeltaTime() * _speed;
			break;
		}

		_pos.y -= _jumpPower;

		_jumpPower -= 1.9f;

		//cout << _jumpPower << endl;
		cout << _pos.y << endl;
	}

	// ���� �����϶�
	if (_isAttack)
	{
		_curWeapon->update();
	}

	// �ǰ� �����϶�
	if (_isHit)
	{
		CAMERA->setShakeCount(25);

		if (_effectAlpha == 50)
		{
			SOUNDMANAGER->play("hurt" + to_string(RND->getFromIntTo(1, 6)));
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
		_curWeapon->render(hdc);
	}

	// �ǰ� ���
	if (_isHit)
	{
		IMAGEMANAGER->findImage("hit_effect")->alphaRender(hdc, _effectAlpha);
	}

	// ���� ���� ��
	_curShovel->getImg()->frameRender(hdc,
		40 - _curShovel->getImg()->getFrameWidth() / 2,
		45 - _curShovel->getImg()->getFrameHeight() / 2);

	// ���� ���� ����
	_curWeapon->getImg()->frameRender(hdc,
		110 - _curWeapon->getImg()->getFrameWidth() / 2,
		45 - _curWeapon->getImg()->getFrameHeight() / 2);

	// �׸��� �̹���
	_shadowImg->alphaRender(hdc,
		CAMERA->getPos().x + 8 + _pos.x,
		CAMERA->getPos().y - 11,
		_shadowAlpha);

	// ���� �̹���
	_bodyImg->frameAlphaRender(hdc,
		CAMERA->getPos().x + 12 + _pos.x,
		CAMERA->getPos().y + _pos.y,
		_bodyImg->getFrameX(), ((int)_curArmor->getArmorType() * 2) + _isLeft,
		_playerAlpha);

	// �Ӹ� �̹���
	_headImg->frameAlphaRender(hdc,
		CAMERA->getPos().x + 15 +_pos.x,
		CAMERA->getPos().y - 18 + _pos.y,
		_headImg->getFrameX(), _isLeft,
		_playerAlpha);


	// �÷��̾� ���� �ε��� ��ǥ
	char currentIdx[40];
	sprintf_s(currentIdx, "Current Index : [%d, %d]", _posIdx.y, _posIdx.x);
	TextOut(hdc, WINSIZE_X - 150, WINSIZE_Y - 40, currentIdx, strlen(currentIdx));
}