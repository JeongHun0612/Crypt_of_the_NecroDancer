#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
    _pos = { (float)WINSIZE_X_HALF - 32.f, (float)WINSIZE_Y_HALF - 32.f };

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
