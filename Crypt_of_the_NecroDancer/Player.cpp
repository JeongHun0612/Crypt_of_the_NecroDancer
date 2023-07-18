#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");

	_posIdxX = 0;
	_posIdxY = 0;
	_pos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };

	_curShovel = new Shovel;
	_curShovel->init();

	_curWeapon = new Weapon;
	_curWeapon->init(WEAPON_TYPE::DAGGER);

	_curArmor.init();

	_rc = RectMakeCenter(_pos.x, _pos.y, 64, 64);
	_curDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = 6;

	_lightPower = 5;

	_coin = 123;
	_diamond = 0;

	_isMove = false;
	_isLeft = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
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

	// 움직임 상태일때
	if (_isMove)
	{
		moveAction(_curDirection);
	}

	// 공격 상태일때
	if (_curWeapon->getIsAttack())
	{
		_curWeapon->update();
	}
}

void Player::render(HDC hdc)
{
	// 플레이어 그리기
	//DrawRectMake(hdc, _rc);
	
	// 삽 모션
	if (_curShovel->getIsDig())
	{
		showShovel(_curDirection, hdc);

		if (SOUNDMANAGER->getPosition("dig_fail") == 417)
		{
			_curShovel->setIsDig(false);
		}
	}

	// 공격 모션
	if (_curWeapon->getIsAttack())
	{
		showAttackEffect(_curDirection, hdc);
	}

	// 현재 착용 삽
	_curShovel->getImg()->frameRender(hdc,
		40 - _curShovel->getImg()->getFrameWidth() / 2,
		45 - _curShovel->getImg()->getFrameHeight() / 2);

	// 현재 착용 무기
	_curWeapon->getImg()->frameRender(hdc, 
		110 - _curWeapon->getImg()->getFrameWidth() / 2,
		45 - _curWeapon->getImg()->getFrameHeight() / 2);

	// 몸통 이미지
	_bodyImg->frameRender(hdc,
		_pos.x - _bodyImg->getFrameWidth() / 2,
		_pos.y - _bodyImg->getFrameHeight() / 2 + 10,
		_bodyImg->getFrameX(), _bodyImg->getFrameY());

	// 머리 이미지
	_headImg->frameRender(hdc,
		_pos.x - _headImg->getFrameWidth() / 2,
		_pos.y - _headImg->getFrameHeight() / 2 - 11,
		_headImg->getFrameX(), _headImg->getFrameY());

	// 플레이어 현재 인덱스 좌표
	char playerIdx[40];
	sprintf_s(playerIdx, "Player Index : [%d, %d]", _posIdxX, _posIdxY);
	TextOut(hdc, WINSIZE_X - 150, WINSIZE_Y - 40, playerIdx, strlen(playerIdx));
}

void Player::moveAction(PLAYER_DIRECTION direction)
{
	switch (direction)
	{
	case PLAYER_DIRECTION::LEFT:
		_isLeft = true;
		_bodyImg->setFrameX(4);
		_headImg->setFrameX(4);
		break;
	case PLAYER_DIRECTION::RIGHT:
		_isLeft = false;
		_bodyImg->setFrameX(0);
		_headImg->setFrameX(0);
		break;
	}

	_curDirection = PLAYER_DIRECTION::NONE;

	static int jumpCount = 0;

	_pos.y += (jumpCount < 8) ? -2 : 2;

	jumpCount++;

	if (jumpCount == 16)
	{
		jumpCount = 0;
		_isMove = false;
	}
}

void Player::showShovel(PLAYER_DIRECTION direction, HDC hdc)
{
	switch (direction)
	{
	case PLAYER_DIRECTION::LEFT:
		_curShovel->getImg()->frameRender(hdc, _pos.x - 90, _pos.y - 25);
		break;
	case PLAYER_DIRECTION::RIGHT:
		_curShovel->getImg()->frameRender(hdc, _pos.x + 40, _pos.y - 25);
		break;
	case PLAYER_DIRECTION::UP:
		_curShovel->getImg()->frameRender(hdc, _pos.x - 25, _pos.y - 90);
		break;
	case PLAYER_DIRECTION::DOWN:
		_curShovel->getImg()->frameRender(hdc, _pos.x - 25, _pos.y + 40);
		break;
	}
}

void Player::showAttackEffect(PLAYER_DIRECTION direction, HDC hdc)
{
	switch (direction)
	{
	case PLAYER_DIRECTION::LEFT:
		_curWeapon->getEffectImg()->frameRender(hdc, _pos.x - 90, _pos.y - 25, 0, 2);
		break;
	case PLAYER_DIRECTION::RIGHT:
		_curWeapon->getEffectImg()->frameRender(hdc, _pos.x + 40, _pos.y - 25, 0, 3);
		break;
	case PLAYER_DIRECTION::UP:
		_curWeapon->getEffectImg()->frameRender(hdc, _pos.x - 25, _pos.y - 90, 0, 0);
		break;
	case PLAYER_DIRECTION::DOWN:
		_curWeapon->getEffectImg()->frameRender(hdc, _pos.x - 25, _pos.y + 40, 0, 1);
		break;
	}
}
