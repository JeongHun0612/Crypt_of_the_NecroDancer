#include "Stdafx.h"
#include "Slime_Green.h"

HRESULT Slime_Green::init(POINT pos, int heart)
{
	_img = IMAGEMANAGER->findImage("slime_green");
	_pos = pos;
	_heart = heart;

	_img->setFrameY(1);

	return S_OK;
}

void Slime_Green::release()
{
}

void Slime_Green::update()
{
}

void Slime_Green::render()
{
	_img->frameRender(getMemDC(), _pos.x, _pos.y, _img->getFrameX(), _img->getFrameY());
}
