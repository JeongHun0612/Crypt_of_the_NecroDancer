#include "Stdafx.h"
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

void Shovel::slotRender(HDC hdc, Vec2_F pos)
{
	Item::slotRender(hdc, pos);
}
