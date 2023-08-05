#include "../../../../2DFrameWork/PCH/Stdafx.h"
#include "Shovel.h"

HRESULT Shovel::init()
{
	_slotImg = IMAGEMANAGER->findImage("slot_shovel");
	_img.img = IMAGEMANAGER->findImage("shovel");

	_hardNess = 1;

	_destoryTime = 0.0f;

	_isDestory = false;

	return S_OK;
}

HRESULT Shovel::init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price, int tileMaxCol)
{
	return S_OK;
}

void Shovel::release()
{
	Item::release();
}

void Shovel::update()
{
	Item::update();

	_destoryTime += TIMEMANAGER->getDeltaTime();

	if (_destoryTime >= 0.2f)
	{
		_isDestory = true;
	}
}

void Shovel::render(HDC hdc)
{
	Item::render(hdc);
}

void Shovel::effectRender(HDC hdc)
{
	_img.img->frameRender(hdc,
		(CAMERA->getPos().x - (PLAYER->getPosIdx().x - _posIdx.x) * 64) + 32 - _img.img->getFrameWidth() / 2,
		(CAMERA->getPos().y - (PLAYER->getPosIdx().y - _posIdx.y) * 64) + 32 - _img.img->getFrameHeight(),
		_img.frameX,
		_img.img->getFrameY());
}

void Shovel::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);
}
