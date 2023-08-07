#include "../../../2DFrameWork/PCH/Stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");
	_freezingImg.img = IMAGEMANAGER->findImage("freezing");
	_freezingImg.alpha = 255;

	// 아이템 초기화
	_curShovel = new Shovel;
	_curShovel->init();
	UIMANAGER->getEquipment().push_back(_curShovel);

	_curWeapon = new Weapon;
	_curWeapon->init();
	UIMANAGER->getEquipment().push_back(_curWeapon);

	_curBomb = new Bomb;
	_curBomb->init();
	UIMANAGER->getExpendable().push_back(_curBomb);


	return S_OK;
}

HRESULT Player::init(int startIdxX, int startIdxY, vector<vector<Tile*>>& vTiles)
{
	_vTiles = vTiles;
	_vTerrainTile = _vTiles[(int)TILE_TYPE::TERRAIN];
	_vWallTile = _vTiles[(int)TILE_TYPE::WALL];

	_tileMaxCol = MAX_LOBBY_COL;

	_pos = { (float)WINSIZE_X_HALF - 32.0f, (float)WINSIZE_Y_HALF - 32.0f };
	_posIdx = { startIdxX , startIdxY };
	_nextPosIdx = { startIdxX , startIdxY };

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 12;
	_curHP = _maxHP;

	_speed = 6.5f;
	_jumpPower = 10.0f;
	_lightPower = 6;

	_stepCount = 0;
	_beatCount = 0;
	_prevBeatCount = 0;

	_playerAlpha = 255;
	_shadowAlpha = 150;
	_effectAlpha = 50;

	_coin = 0;
	_diamond = 0;

	_isLeft = false;
	_isMove = false;
	_isAttack = false;
	_isHit = false;
	_isBomb = false;
	_isInvincible = false;
	_isGrab = false;
	_isIce = false;
	_isNextStage = false;

	if (_curWeapon->getType() != (int)WEAPON_TYPE::DAGGER)
	{
		_curWeapon->init();
	}

	if (_curBomb == nullptr)
	{
		_curBomb = new Bomb;
		_curBomb->init();
		UIMANAGER->getExpendable().push_back(_curBomb);
	}

	if (_curArmor != nullptr)
	{
		UIMANAGER->deleteEquiment(_curArmor);
		_curArmor = nullptr;
	}

	if (_curPotion != nullptr)
	{
		UIMANAGER->deleteExpendable(_curPotion);
		_curPotion = nullptr;
	}

	return S_OK;
}

HRESULT Player::init(int startIdxX, int startIdxY, vector<Enemy*>& vEnemy, vector<Item*>& vItem, vector<vector<Tile*>>& vTiles, int tileMaxCol)
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

	_stepCount = 0;
	_beatCount = 0;
	_prevBeatCount = 0;

	_curDirection = PLAYER_DIRECTION::NONE;
	_nextDirection = PLAYER_DIRECTION::NONE;

	_playerAlpha = 255;
	_shadowAlpha = 150;
	_effectAlpha = 50;

	_isLeft = false;
	_isMove = false;
	_isAttack = false;
	_isHit = false;
	_isBomb = false;
	_isInvincible = false;
	_isIce = false;
	_isGrab = false;
	_isNextStage = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	// 플레이어 프레임 이미지 변경
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

	// 플레이어 키입력 동작
	if (!_isMove && !_isIce)
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

		// 폭탄 사용
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (_curBomb != nullptr)
			{
				_isBomb = true;

				_curBomb->setPosIdx(_posIdx.x, _posIdx.y);

				SOUNDMANAGER->play("bomb_lit");
				UIMANAGER->deleteExpendable(_curBomb);
			}
		}

		// 아이템 사용
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (_curPotion != nullptr)
			{
				_curHP += _curPotion->getRecoveryAmount();
				if (_curHP > _maxHP)
				{
					_curHP = _maxHP;
				}

				SOUNDMANAGER->play("item_food");
				UIMANAGER->deleteExpendable(_curPotion);
				_curPotion = nullptr;
			}
		}
	}

	int _curTileIdx = (_tileMaxCol * _posIdx.y) + _posIdx.x;

	int _curBottomTilIdx = _curTileIdx + _tileMaxCol;

	if (_vEnemy.size() != TILEMAP->getEnemyList().size())
	{
		_vEnemy = TILEMAP->getEnemyList();
	}

	// 캐릭터 아래 쪽에 타일이 있을 시 그림자 숨기기
	if (_vWallTile[_curBottomTilIdx]->_idxX == _posIdx.x && _vWallTile[_curBottomTilIdx]->_idxY == _posIdx.y + 1 && _vWallTile[_curBottomTilIdx]->_isExist)
	{
		_shadowAlpha = 0;
	}

	_beatCount = BEAT->getBeatCount();

	if (_prevBeatCount < _beatCount)
	{
		_stepCount++;
		_prevBeatCount = _beatCount;
	}

	// 키 입력을 받고 다음 행동에 대한 방향이 정해졌을 때
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
				// 벽 충돌체 발견 시
				if (_vWallTile[_nextTileIdx]->_isCollider)
				{
					_isMove = false;

					// 충돌체가 현재 플레이어가 가진 삽의 강도보다 단단할 시
					if (_vWallTile[_nextTileIdx]->_hardNess > _curShovel->getHardNess())
					{
						SOUNDMANAGER->play("dig_fail");
						addShowShovel(_nextPosIdx.x, _nextPosIdx.y);
					}
					else
					{
						// 벽 부수기
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

			// 적 객체 검사
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

					// 적을 Hit 상태로 만든다
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

	// 움직임 상태일때
	if (_isMove)
	{
		_pos.y -= _jumpPower;

		_jumpPower -= 2.223f;

		if (_pos.y <= 338.0f || _pos.y >= 370.0f)
		{
			_pos.y = (float)WINSIZE_Y_HALF - 32.0f;
		}
	}

	// 삽질 상태일때
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

	// 폭탄을 사용했을 때
	if (_isBomb)
	{
		_curBomb->update();
	}

	// 피격 상태일때
	if (_isHit)
	{
		_stepCount = 0;
		CAMERA->setShakeCount(25);

		if (_effectAlpha == 50 && !_isInvincible)
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
			SOUNDMANAGER->play("death");
			_isHit = false;
		}
	}

	// 무적 상태일 때
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

		if (_stepCount == 2)
		{
			_playerAlpha = 255;
			_isInvincible = false;
		}
	}

	if (_isIce)
	{
		if (_stepCount > 2)
		{
			if (_freezingImg.alpha == 255)
			{
				_freezingImg.alpha = 0;
			}
			else
			{
				_freezingImg.alpha = 255;
			}
		}

		if (_stepCount == 4)
		{
			_freezingImg.alpha = 255;
			_isIce = false;
		}
	}
}

void Player::render(HDC hdc)
{
	// 공격 모션
	if (_isAttack)
	{
		_curWeapon->effectRender(hdc);
	}

	// 피격 모션
	if (_isHit)
	{
		IMAGEMANAGER->findImage("hit_effect")->alphaRender(hdc, _effectAlpha);
	}

	// 삽 모션
	for (auto iter = _vShowShovel.begin(); iter != _vShowShovel.end(); ++iter)
	{
		iter->effectRender(hdc);
	}

	// 폭탄 설치
	if (_isBomb)
	{
		_curBomb->effectRender(hdc);
	}

	// 그림자 이미지
	_shadowImg->alphaRender(hdc,
		_pos.x + 8.0f,
		_pos.y - 11.0f,
		_shadowAlpha);

	// 몸통 이미지
	if (_curArmor != nullptr)
	{
		_bodyImg->frameAlphaRender(hdc,
			_pos.x + 12.0f,
			_pos.y,
			_bodyImg->getFrameX(), (_curArmor->getType() * 2) + _isLeft,
			_playerAlpha);
	}
	else
	{
		_bodyImg->frameAlphaRender(hdc,
			_pos.x + 12.0f,
			_pos.y,
			_bodyImg->getFrameX(), _isLeft,
			_playerAlpha);
	}

	// 머리 이미지
	_headImg->frameAlphaRender(hdc,
		_pos.x + 15.0f,
		_pos.y - 18.0f,
		_headImg->getFrameX(), _isLeft,
		_playerAlpha);

	// 빙결 이미지
	if (_isIce)
	{
		_freezingImg.img->alphaRender(hdc,
			WINSIZE_X_HALF - _freezingImg.img->getWidth() / 2,
			WINSIZE_Y_HALF - 10,
			_freezingImg.alpha);
	}


	// 플레이어 현재 인덱스 좌표
	//char currentIdx[40];
	//sprintf_s(currentIdx, "Current Index : [%d, %d]", _posIdx.y, _posIdx.x);
	//TextOut(hdc, WINSIZE_X - 150, WINSIZE_Y - 40, currentIdx, strlen(currentIdx));
}

void Player::addShowShovel(int idxX, int idxY)
{
	Shovel showShovel = *_curShovel;
	showShovel.setPosIdx(idxX, idxY);

	_vShowShovel.push_back(showShovel);
}