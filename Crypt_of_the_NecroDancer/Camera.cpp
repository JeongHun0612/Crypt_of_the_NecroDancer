#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
	_pos = { (float)WINSIZE_X_HALF - 32.f, (float)WINSIZE_Y_HALF - 32.f };
	_prevPos = { (float)WINSIZE_X_HALF - 32.f, (float)WINSIZE_Y_HALF - 32.f };

	_shakeCount = 0;

	return S_OK;
}

void Camera::release(void)
{
}

void Camera::update(void)
{
	if (_shakeCount > 0)
	{
		_shakeCount--;

		_pos.x -= RND->getFromFloatTo(-2.0f, 2.0f);
		_pos.y -= RND->getFromFloatTo(-2.0f, 2.0f);

		if (_shakeCount == 0)
		{
			_pos.x = _prevPos.x;
			_pos.y = _prevPos.y;
		}
	}

	if (PLAYER->getIsMove())
	{
		switch (PLAYER->getCurDirection())
		{
		case PLAYER_DIRECTION::LEFT:
			_pos.x += 64 * TIMEMANAGER->getDeltaTime() * 8.f;
			break;
		case PLAYER_DIRECTION::RIGHT:
			_pos.x -= 64 * TIMEMANAGER->getDeltaTime() * 8.f;
			break;
		case PLAYER_DIRECTION::UP:
			_pos.y += 64 * TIMEMANAGER->getDeltaTime() * 8.f;
			break;
		case PLAYER_DIRECTION::DOWN:
			_pos.y -= 64 * TIMEMANAGER->getDeltaTime() * 8.f;
			break;
		}

		if (_pos.x >= (float)WINSIZE_X_HALF - 32.f + 64.f || _pos.x <= (float)WINSIZE_X_HALF - 32.f - 64.f ||
			_pos.y >= (float)WINSIZE_Y_HALF - 32.f + 64.f || _pos.y <= (float)WINSIZE_Y_HALF - 32.f - 64.f)
		{
			// 플레이어 위치 좌표 설정
			PLAYER->setPosIdxX(PLAYER->getNextIdxX());
			PLAYER->setPosIdxY(PLAYER->getNextIdxY());

			PLAYER->setNextIdxX(PLAYER->getPosIdxX());
			PLAYER->setNextIdxY(PLAYER->getPosIdxY());

			_pos.x = _prevPos.x;
			_pos.y = _prevPos.y;

			PLAYER->setShadowAlpha(130);
			PLAYER->setIsMove(false);
		}
	}
}