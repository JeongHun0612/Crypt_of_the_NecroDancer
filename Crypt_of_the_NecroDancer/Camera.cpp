#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
    _targetPos = { 0.0f, 0.0f };

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

