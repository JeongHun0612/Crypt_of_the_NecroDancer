#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
    _posX = 0.0f;
    _posY = 0.0f;
    _moveSpeed = 5.0f;

    return S_OK;
}

void Camera::release(void)
{
}

void Camera::update(void)
{
}

void Camera::render(HDC hdc)
{
}
