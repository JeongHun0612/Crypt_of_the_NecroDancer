#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_headImg = IMAGEMANAGER->findImage("player_head");
	_bodyImg = IMAGEMANAGER->findImage("player_body");

	_posIdx = { 1, 1 };
	_pos = { WINSIZE_X_HALF, WINSIZE_Y_HALF };

	_rc = RectMakeCenter(_pos.x, _pos.y, 64, 64);
	_curDirection = PLAYER_DIRECTION::NONE;

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

	if (_isMove)
	{
		moveAction(_curDirection);
	}

	if (!_isMove && BEAT->getBeat())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_curDirection = PLAYER_DIRECTION::LEFT;
			_isLeft = true;
			_bodyImg->setFrameX(4);
			_headImg->setFrameX(4);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_curDirection = PLAYER_DIRECTION::RIGHT;
			_isLeft = false;
			_bodyImg->setFrameX(0);
			_headImg->setFrameX(0);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_curDirection = PLAYER_DIRECTION::UP;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_curDirection = PLAYER_DIRECTION::DOWN;
		}

		if (_curDirection != PLAYER_DIRECTION::NONE)
		{
			_isMove = true;
			BEAT->setSuccess(true);
		}
	}
}

void Player::render(HDC hdc)
{
	// 플레이어 그리기
	DrawRectMake(hdc, _rc);

	_bodyImg->frameRender(hdc,
		_pos.x - _bodyImg->getFrameWidth() / 2,
		_pos.y - _bodyImg->getFrameHeight() / 2 + 10,
		_bodyImg->getFrameX(), _bodyImg->getFrameY());

	_headImg->frameRender(hdc,
		_pos.x - _headImg->getFrameWidth() / 2,
		_pos.y - _headImg->getFrameHeight() / 2 - 11,
		_headImg->getFrameX(), _headImg->getFrameY());
}

void Player::moveAction(PLAYER_DIRECTION direction)
{
	static int jumpCount = 0;

	switch (direction)
	{
	case PLAYER_DIRECTION::LEFT:
		_pos.x -= 4;
		break;
	case PLAYER_DIRECTION::RIGHT:
		_pos.x += 4;
		break;
	case PLAYER_DIRECTION::UP:
		_pos.y -= 4;
		break;
	case PLAYER_DIRECTION::DOWN:
		_pos.y += 4;
		break;
	}

	_pos.y += (jumpCount < 8) ? -2 : 2;

	jumpCount++;

	if (jumpCount == 16)
	{
		jumpCount = 0;
		_isMove = false;
		_curDirection = PLAYER_DIRECTION::NONE;
		_rc = RectMakeCenter(_pos.x, _pos.y, TILESIZE, TILESIZE);
		_posIdx = { _pos.x / TILESIZE, _pos.y / TILESIZE };
		BEAT->setSuccess(false);
	}
}
