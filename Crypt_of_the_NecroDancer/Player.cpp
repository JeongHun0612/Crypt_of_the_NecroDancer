#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");

	_pos = { WINSIZE_X / 2, WINSIZE_Y / 2 + 16 };

	_rc = RectMake(_pos.x, _pos.y, 64, 64);
	_curDirection = PLAYER_DIRECTION::NONE;

	_isMove = false;

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= 0.2f)
	{
		_headImg->setFrameX(_headImg->getFrameX() + 1);
		_bodyImg->setFrameX(_bodyImg->getFrameX() + 1);

		if (_headImg->getFrameX() == _headImg->getMaxFrameX() / 2)
		{
			_bodyImg->setFrameX(0);
			_headImg->setFrameX(0);
		}

		_count = 0.0f;
	}

	if (_isMove)
	{
		moveAction(_curDirection);
	}

	if (!_isMove)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_curDirection = PLAYER_DIRECTION::LEFT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_curDirection = PLAYER_DIRECTION::RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_curDirection = PLAYER_DIRECTION::UP;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_curDirection = PLAYER_DIRECTION::DOWN;
			_isMove = true;
		}

		if (_curDirection != PLAYER_DIRECTION::NONE)
		{
			_isMove = true;
		}
	}
}

void Player::render(void)
{
	// 플레이어 그리기
	_bodyImg->frameRender(getMemDC(),
		_pos.x + _headImg->getFrameWidth() / 2,
		_pos.y + _headImg->getFrameHeight() / 2 + 16,
		_bodyImg->getFrameX(), _bodyImg->getFrameY());

	_headImg->frameRender(getMemDC(),
		_pos.x + _headImg->getFrameWidth() / 2,
		_pos.y + _headImg->getFrameHeight() / 2,
		_headImg->getFrameX(), _headImg->getFrameY());
}

void Player::moveAction(PLAYER_DIRECTION direction)
{
	static int jumpCount = 0;

	switch (direction)
	{
	case PLAYER_DIRECTION::LEFT:
		_pos.x -= 8;
		break;
	case PLAYER_DIRECTION::RIGHT:
		_pos.x += 8;
		break;
	case PLAYER_DIRECTION::UP:
		_pos.y -= 8;
		break;
	case PLAYER_DIRECTION::DOWN:
		_pos.y += 8;
		break;
	}

	_rc = RectMake(_pos.x, _pos.y - 8, 64, 64);

	_pos.y += (jumpCount < 4) ? -4 : 4;

	jumpCount++;

	if (jumpCount == 8)
	{
		jumpCount = 0;
		_isMove = false;
		_curDirection = PLAYER_DIRECTION::NONE;
	}
}
