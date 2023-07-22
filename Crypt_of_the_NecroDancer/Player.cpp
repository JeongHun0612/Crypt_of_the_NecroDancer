#include "Stdafx.h"
#include "Player.h"
#include "TileMap.h"

HRESULT Player::init(int startIdxX, int startIxY, vector<vector<Tile*>> tiles, int tileMaxCol)
{
	_vTiles = tiles;
	_vTerrainTile = _vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = _vTiles[(int)TILE_TYPE::WALL];

	_vEnemy = ENEMYMANAGER->getEnemyList();

	_tileMaxCol = tileMaxCol;

	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");

	_pos = { WINSIZE_X_HALF, WINSIZE_Y_HALF };
	_posIdx = { 5 , 5 };
	_nextPosIdx = { _posIdx.x , _posIdx.y };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = _maxHP;

	_jumpPower = 8.f;
	_lightPower = 5;
	_effectAlpha = 50;
	_shadowAlpha = 130;

	_coin = 0;
	_diamond = 0;

	_isMove = false;
	_isLeft = false;

	_curShovel = new Shovel;
	_curShovel->init();

	_curWeapon = new Weapon;
	_curWeapon->init(WEAPON_TYPE::DAGGER);

	_curArmor.init();

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	// �÷��̾� ������ �̹��� ����
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.15f)
	{
		if (_isLeft)
		{
			if (_headImg->getFrameX() == _headImg->getMaxFrameX())
			{
				_bodyImg->setFrameX(4);
				_headImg->setFrameX(4);
			}
		}
		else
		{
			if (_headImg->getFrameX() == _headImg->getMaxFrameX() / 2)
			{
				_bodyImg->setFrameX(0);
				_headImg->setFrameX(0);
			}
		}

		_headImg->setFrameX(_headImg->getFrameX() + 1);
		_bodyImg->setFrameX(_bodyImg->getFrameX() + 1);

		_count = 0.0f;
	}

	// �÷��̾� Ű�Է� ����
	if (!_isMove)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_nextDirection = PLAYER_DIRECTION::LEFT;
			_isLeft = true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_nextDirection = PLAYER_DIRECTION::RIGHT;
			_isLeft = false;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_nextDirection = PLAYER_DIRECTION::UP;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_nextDirection = PLAYER_DIRECTION::DOWN;
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
			_curDirection = _nextDirection;

			_nextPosIdx.x = _posIdx.x + _fourDirection[(int)_curDirection].x;
			_nextPosIdx.y = _posIdx.y + _fourDirection[(int)_curDirection].y;

			int _nextTileIdx = (_tileMaxCol * _nextPosIdx.y) + _nextPosIdx.x;

			// �� �浹ü �߰� ��
			if (_vWallTile[_nextTileIdx]->_isCollider)
			{
				_isMove = false;

				// �浹ü�� ���� �÷��̾ ���� ���� �������� �ܴ��� ��
				if (_vWallTile[_nextTileIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
				{
					_curShovel->addShowShovel(_nextPosIdx.x, _nextPosIdx.y);
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

			// �� ��ü �˻�
			for (auto iter = _vEnemy.begin(); iter != _vEnemy.end();)
			{
				if ((*iter)->getPosIdx().x == _nextPosIdx.x && (*iter)->getPosIdx().y == _nextPosIdx.y)
				{
					_isMove = false;
					_isAttack = true;
					CAMERA->setShakeCount(15);
					SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));

					// �� HP�� ���� ������ ���⸸ŭ ����
					(*iter)->setCurHP((*iter)->getCurHP() - _curWeapon->getPower());

					// �� HP�� 0 ���Ϸ� �������� �� ��ü ���� �� ���� ����
					if ((*iter)->getCurHP() <= 0)
					{
						(*iter)->release();
						delete(*iter);
						iter = _vEnemy.erase(iter);
					}
					else ++iter;
					break;
				}
				else ++iter;
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
		moveAction();
	}
	else
	{
		_pos.y = (float)WINSIZE_Y_HALF;
		_jumpPower = 8.f;
	}

	// ���� �����϶�
	if (_isAttack)
	{
		_curWeapon->update();
	}

	// �ǰ� �����϶�
	if (_isHit)
	{
		CAMERA->setShakeCount(20);

		if (_effectAlpha == 50)
		{
			SOUNDMANAGER->play("hurt" + to_string(RND->getFromIntTo(1, 6)));
		}

		_effectAlpha -= 10;

		if (_effectAlpha <= 0)
		{
			_effectAlpha = 50;
			_isHit = false;

			if (_curHP <= 0)
			{
				cout << "���" << endl;
			}
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
		_pos.x - _shadowImg->getWidth() / 2,
		WINSIZE_Y_HALF - 45,
		_shadowAlpha);

	// ���� �̹���
	_bodyImg->frameRender(hdc,
		_pos.x - _bodyImg->getFrameWidth() / 2,
		_pos.y - _bodyImg->getFrameHeight() / 2 - 20,
		_bodyImg->getFrameX(), _bodyImg->getFrameY());

	// �Ӹ� �̹���
	_headImg->frameRender(hdc,
		_pos.x - _headImg->getFrameWidth() / 2,
		_pos.y - _headImg->getFrameHeight() / 2 - 45,
		_headImg->getFrameX(), _headImg->getFrameY());


	// �÷��̾� ���� �ε��� ��ǥ
	char currentIdx[40];
	sprintf_s(currentIdx, "Current Index : [%d, %d]", _posIdx.y, _posIdx.x);
	TextOut(hdc, WINSIZE_X - 150, WINSIZE_Y - 40, currentIdx, strlen(currentIdx));
}

void Player::moveAction()
{
	if (_isLeft)
	{
		_headImg->setFrameX(4);
		_bodyImg->setFrameX(4);
	}
	else
	{
		_headImg->setFrameX(0);
		_bodyImg->setFrameX(0);
	}

	_pos.y -= _jumpPower;

	_jumpPower -= 2.0f;

	if (_pos.y >= (float)WINSIZE_Y_HALF)
	{
		_isMove = false;
	}
}