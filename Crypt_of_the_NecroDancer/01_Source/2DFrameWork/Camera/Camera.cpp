#include "../PCH/Stdafx.h"
#include "../Camera/Camera.h"

HRESULT Camera::init(void)
{
	_pos = { (float)WINSIZE_X_HALF - 32.f, (float)WINSIZE_Y_HALF - 32.f };
	_prevPos = { (float)WINSIZE_X_HALF - 32.f, (float)WINSIZE_Y_HALF - 32.f };

	_shakeCount = 0;
	_cameraSpeed = 6.5f;

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

		if (_shakeCount == 0 || PLAYER->getIsMove())
		{
			_pos.x = _prevPos.x;
			_pos.y = _prevPos.y;
			_shakeCount = 0;
		}
	}

	if (PLAYER->getIsMove())
	{
		switch (PLAYER->getCurDirection())
		{
		case PLAYER_DIRECTION::LEFT:
			_pos.x += 64 * TIMEMANAGER->getDeltaTime() * _cameraSpeed;
			break;
		case PLAYER_DIRECTION::RIGHT:
			_pos.x -= 64 * TIMEMANAGER->getDeltaTime() * _cameraSpeed;
			break;
		case PLAYER_DIRECTION::UP:
			_pos.y += 64 * TIMEMANAGER->getDeltaTime() * _cameraSpeed;
			break;
		case PLAYER_DIRECTION::DOWN:
			_pos.y -= 64 * TIMEMANAGER->getDeltaTime() * _cameraSpeed;
			break;
		}

		if (_pos.x >= _prevPos.x + 64.f || _pos.x <= _prevPos.x - 64.f || _pos.y >= _prevPos.y + 64.f || _pos.y <= _prevPos.y - 64.f)
		{
			// 플레이어 위치 좌표 설정
			PLAYER->setPos((float)WINSIZE_X_HALF - 32.0f, (float)WINSIZE_Y_HALF - 32.0f);
			PLAYER->setPosIdx(PLAYER->getNextPosIdx().x, PLAYER->getNextPosIdx().y);
			PLAYER->setNextPosIdx(PLAYER->getPosIdx().x, PLAYER->getPosIdx().y);
			PLAYER->setShadowAlpha(150);

			_pos.x = _prevPos.x;
			_pos.y = _prevPos.y;

			PLAYER->setIsMove(false);
		}
	}
}