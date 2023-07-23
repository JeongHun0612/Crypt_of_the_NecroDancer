#include "Stdafx.h"
#include "Player.h"
#include "TileMap.h"

HRESULT Player::init()
{
	cout << "플레이어 초기화" << endl;

	return S_OK;
}

HRESULT Player::init(int startIdxX, int startIxY)
{
	_vTiles = TILEMAP->getLoobyTiles();
	_vTerrainTile = _vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = _vTiles[(int)TILE_TYPE::WALL];

	_tileMaxCol = MAX_LOBBY_COL;

	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");

	_pos = { WINSIZE_X_HALF, WINSIZE_Y_HALF };
	_posIdx = { startIdxX , startIxY };
	_nextPosIdx = { startIdxX , startIxY };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = _maxHP;

	_jumpPower = 8.0f;
	_lightPower = 5;
	_effectAlpha = 50;
	_shadowAlpha = 130;

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

HRESULT Player::init(int startIdxX, int startIxY, vector<vector<Tile*>> tiles, int tileMaxCol)
{
	_vTiles = tiles;
	_vTerrainTile = _vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = _vTiles[(int)TILE_TYPE::WALL];

	_vEnemy = ENEMYMANAGER->getEnemyList();

	_tileMaxCol = tileMaxCol;

	_posIdx = { startIdxX , startIxY };
	_nextPosIdx = { startIdxX , startIxY };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = _maxHP;

	_isMove = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	// 플레이어 프레임 이미지 변경
	_count += TIMEMANAGER->getDeltaTime();

	if (_count >= 0.15f)
	{
		if (_headImg->getFrameX() == _headImg->getMaxFrameX())
		{
			_bodyImg->setFrameX(0);
			_headImg->setFrameX(0);
		}

		_headImg->setFrameX(_headImg->getFrameX() + 1);
		_bodyImg->setFrameX(_bodyImg->getFrameX() + 1);

		_count = 0.0f;
	}

	// 플레이어 키입력 동작
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

	// 캐릭터 아래 쪽에 타일이 있을 시 그림자 숨기기
	if (_vWallTile[_curBottomTilIdx]->_idxX == _posIdx.x && _vWallTile[_curBottomTilIdx]->_idxY == _posIdx.y + 1 && _vWallTile[_curBottomTilIdx]->_isExist)
	{
		_shadowAlpha = 0;
	}

	// 키 입력을 받고 다음 행동에 대한 방향이 정해졌을 때
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

			// 벽 충돌체 발견 시
			if (_vWallTile[_nextTileIdx]->_isCollider)
			{
				_isMove = false;
				_curShovel->addShowShovel(_nextPosIdx.x, _nextPosIdx.y);

				// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
				if (_vWallTile[_nextTileIdx]->_hardNess > PLAYER->getCurShovel()->getHardNess())
				{
					SOUNDMANAGER->play("dig_fail");
				}
				else
				{
					// 벽 부수기
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

			// 적 객체 검사
			for (auto iter = _vEnemy.begin(); iter != _vEnemy.end();)
			{
				if ((*iter)->getPosIdx().x == _nextPosIdx.x && (*iter)->getPosIdx().y == _nextPosIdx.y)
				{
					_isMove = false;
					_isAttack = true;
					CAMERA->setShakeCount(15);
					SOUNDMANAGER->play("melee1_" + to_string(RND->getFromIntTo(1, 4)));

					// 적 HP를 현재 무기의 세기만큼 감소
					(*iter)->setCurHP((*iter)->getCurHP() - _curWeapon->getPower());

					// 적 HP가 0 이하로 내려갔을 때 객체 삭제 및 벡터 삭제
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

	// 움직임 상태일때
	if (_isMove)
	{
		_pos.y -= _jumpPower;

		_jumpPower -= 1.5f;
	}

	// 공격 상태일때
	if (_isAttack)
	{
		_curWeapon->update();
	}

	// 피격 상태일때
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
				cout << "사망" << endl;
			}
		}
	}
}

void Player::render(HDC hdc)
{
	// 공격 모션
	if (_isAttack)
	{
		_curWeapon->render(hdc);
	}

	// 피격 모션
	if (_isHit)
	{
		IMAGEMANAGER->findImage("hit_effect")->alphaRender(hdc, _effectAlpha);
	}

	// 현재 착용 삽
	_curShovel->getImg()->frameRender(hdc,
		40 - _curShovel->getImg()->getFrameWidth() / 2,
		45 - _curShovel->getImg()->getFrameHeight() / 2);

	// 현재 착용 무기
	_curWeapon->getImg()->frameRender(hdc,
		110 - _curWeapon->getImg()->getFrameWidth() / 2,
		45 - _curWeapon->getImg()->getFrameHeight() / 2);

	// 그림자 이미지
	_shadowImg->alphaRender(hdc,
		_pos.x - _shadowImg->getWidth() / 2,
		WINSIZE_Y_HALF - 45,
		_shadowAlpha);

	// 몸통 이미지
	_bodyImg->frameRender(hdc,
		_pos.x - _bodyImg->getFrameWidth() / 2,
		_pos.y - _bodyImg->getFrameHeight() / 2 - 20,
		_bodyImg->getFrameX(), ((int)_curArmor->getArmorType() * 2) + _isLeft);

	// 머리 이미지
	_headImg->frameRender(hdc,
		_pos.x - _headImg->getFrameWidth() / 2 - 1,
		_pos.y - _headImg->getFrameHeight() / 2 - 44,
		_headImg->getFrameX(), _isLeft);


	// 플레이어 현재 인덱스 좌표
	char currentIdx[40];
	sprintf_s(currentIdx, "Current Index : [%d, %d]", _posIdx.y, _posIdx.x);
	TextOut(hdc, WINSIZE_X - 150, WINSIZE_Y - 40, currentIdx, strlen(currentIdx));
}