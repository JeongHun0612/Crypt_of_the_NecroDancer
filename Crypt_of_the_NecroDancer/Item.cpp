#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init()
{
	return S_OK;
}

HRESULT Item::init(int idxX, int idxY, int type)
{
	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
}

void Item::render(HDC hdc)
{
	_img.img->frameRender(hdc,
		(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2,
		(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight(),
		_img.img->getFrameX(),
		_img.img->getFrameY());
}

void Item::render(HDC hdc, Vec2_F pos)
{
	_slotImg->render(hdc, pos.x, pos.y);

	_img.img->frameRender(hdc,
		pos.x + 30 - _img.img->getFrameWidth() / 2,
		pos.y + 30 - _img.img->getFrameHeight() / 2,
		_img.img->getFrameX(),
		_img.img->getFrameY());
}
