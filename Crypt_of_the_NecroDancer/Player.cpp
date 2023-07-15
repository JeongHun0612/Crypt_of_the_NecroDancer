#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");

	_posIdx = { 0, 0 };
	_pos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };

	_rc = RectMakeCenter(_pos.x, _pos.y, 64, 64);
	_curDirection = PLAYER_DIRECTION::NONE;

	_maxHP = 6;
	_curHP = 6;

	_coin = 0;
	_diamond = 0;

	_isMove = false;
	_isLeft = false;

	_isShovel = false;

	_curShovel.img = IMAGEMANAGER->findImage("shovel");
	_curShovel.hardness = 2;

	_weaponItemImg = IMAGEMANAGER->findImage("dagger");

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

	if (_isMove)
	{
		moveAction(_curDirection);
	}
}

void Player::render(HDC hdc)
{
	// 아이템 이미지 그리기
	_curShovel.img->frameRender(hdc, 15, 20, _curShovel.img->getFrameX(), _curShovel.img->getFrameY());
	_weaponItemImg->frameRender(hdc, 100, 35, _weaponItemImg->getFrameX(), _weaponItemImg->getFrameY());

	// 플레이어 그리기
	//DrawRectMake(hdc, _rc);

	_bodyImg->frameRender(hdc,
		_pos.x - _bodyImg->getFrameWidth() / 2,
		_pos.y - _bodyImg->getFrameHeight() / 2 + 10,
		_bodyImg->getFrameX(), _bodyImg->getFrameY());

	_headImg->frameRender(hdc,
		_pos.x - _headImg->getFrameWidth() / 2,
		_pos.y - _headImg->getFrameHeight() / 2 - 11,
		_headImg->getFrameX(), _headImg->getFrameY());

	// 플레이어 현재 인덱스 좌표
	char playerIdx[40];
	sprintf_s(playerIdx, "Player Index : [%d, %d]", _posIdx.x, _posIdx.y);
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
		_posIdx.x--;
		break;
	case PLAYER_DIRECTION::RIGHT:
		_isLeft = false;
		_bodyImg->setFrameX(0);
		_headImg->setFrameX(0);
		_posIdx.x++;
		break;
	case PLAYER_DIRECTION::UP:
		_posIdx.y--;
		break;
	case PLAYER_DIRECTION::DOWN:
		_posIdx.y++;
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
