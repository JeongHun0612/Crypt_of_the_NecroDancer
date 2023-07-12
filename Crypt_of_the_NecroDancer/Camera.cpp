#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
    _pos = { (float)WINSIZE_X_HALF, (float)WINSIZE_Y_HALF };
    _rc = RectMakeCenter(_pos.x, _pos.y, WINSIZE_X + 500, WINSIZE_Y + 300);

    _targetPos = { 0.0f, 0.0f };
    _prevTargetPos = { 0.0f, 0.0f };

    return S_OK;
}

void Camera::release(void)
{
}

void Camera::update(void)
{
    callDiff();
}

void Camera::render(HDC hdc)
{
}

void Camera::callDiff()
{
    _pos.x = ((float)WINSIZE_X_HALF - _targetPos.x) * TIMEMANAGER->getDeltaTime() * 5.f;
    _pos.y = ((float)WINSIZE_Y_HALF - _targetPos.y) * TIMEMANAGER->getDeltaTime() * 5.f;
}

