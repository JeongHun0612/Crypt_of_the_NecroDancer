#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(int startIdxX, int startIxY)
{
	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");
	_shadowImg = IMAGEMANAGER->findImage("shadow_standard");

	_pos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };
	_posIdxX = startIdxX;
	_posIdxY = startIxY;

	_nextIdxX = startIdxX;
	_nextIdxY = startIxY;

	_jumpPower = 8.f;

	_shadowAlpha = 130;

	_curShovel = new Shovel;
	_curShovel->init();

	_curWeapon = new Weapon;
	_curWeapon->init(WEAPON_TYPE::DAGGER);

	_curArmor.init();

	_rc = RectMakeCenter(_pos.x, _pos.y, 64, 64);
	_curDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = _maxHP;

	_lightPower = 5;
	_effectAlpha = 50;

	_coin = 0;
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
	else
	{
		_pos.y = (float)WINSIZE_Y_HALF;
		_jumpPower = 8.f;
		_isMove = false;
	}

	// 공격 상태일때
	_curWeapon->update();

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
		}

		if (_curHP <= 0)
		{
			cout << "사망" << endl;
		}
	}
}

void Player::render(HDC hdc)
{
	// 충돌체 그리기
	if(KEYMANAGER->isToggleKey(VK_F3))
	{
		DrawRectMake(hdc, _rc);
	}

	// 삽 모션
	//_curShovel->render(hdc);

	// 공격 모션
	_curWeapon->render(hdc);

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
		WINSIZE_Y_HALF - 40,
		_shadowAlpha);

	// 몸통 이미지
	_bodyImg->frameRender(hdc,
		_pos.x - _bodyImg->getFrameWidth() / 2,
		_pos.y - _bodyImg->getFrameHeight() / 2 - 15,
		_bodyImg->getFrameX(), _bodyImg->getFrameY());

	// 머리 이미지
	_headImg->frameRender(hdc,
		_pos.x - _headImg->getFrameWidth() / 2,
		_pos.y - _headImg->getFrameHeight() / 2 - 40,
		_headImg->getFrameX(), _headImg->getFrameY());

	// 플레이어 현재 인덱스 좌표
	char playerIdx[40];
	sprintf_s(playerIdx, "Player Index : [%d, %d]", _posIdxY, _posIdxX);
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

	_pos.y -= _jumpPower;

	_jumpPower -= 2.0f;

	if (_pos.y >= (float)WINSIZE_Y_HALF)
	{
		_pos.y = (float)WINSIZE_Y_HALF;
		_jumpPower = 8.f;
		_isMove = false;
	}
}