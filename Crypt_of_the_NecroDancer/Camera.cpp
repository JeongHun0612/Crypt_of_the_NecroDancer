#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
	_pos = { (float)WINSIZE_X_HALF - 32.f, (float)WINSIZE_Y_HALF - 32.f };

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
			_pos.x = (float)WINSIZE_X_HALF - 32.f;
			_pos.y = (float)WINSIZE_Y_HALF - 32.f;
		}
	}
}

void Camera::cameraShake(int shakeCount)
{
	_shakeCount = shakeCount;
}
