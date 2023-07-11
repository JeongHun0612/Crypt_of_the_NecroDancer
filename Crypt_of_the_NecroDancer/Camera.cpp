#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
    _lookPos = { 0, 0 };
    _lookPosIdx = { 0, 0 };

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
