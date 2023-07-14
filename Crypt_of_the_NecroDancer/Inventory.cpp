#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	// Slot 이미지 초기화
	ItemSlot shovelSlot;
	shovelSlot.img = IMAGEMANAGER->findImage("slot_shovel");
	shovelSlot.x = 10;
	shovelSlot.y = 10;
	shovelSlot.type = ITEM_TYPE::SHOVEL;

	_vItemSlot.push_back(shovelSlot);

	ItemSlot attackSlot;
	attackSlot.img = IMAGEMANAGER->findImage("slot_attack");
	attackSlot.x = 80;
	attackSlot.y = 10;
	attackSlot.type = ITEM_TYPE::ATTACK;

	_vItemSlot.push_back(attackSlot);

	ItemSlot bodySlot;
	bodySlot.img = IMAGEMANAGER->findImage("slot_body");
	bodySlot.x = 10;
	bodySlot.y = 80;
	bodySlot.type = ITEM_TYPE::BODY;

	_vItemSlot.push_back(bodySlot);


	// 아이템 초기화
	Item slove;
	slove.img = IMAGEMANAGER->findImage("slot_body");

	return S_OK;
}

void Inventory::release(void)
{
}

void Inventory::render(HDC hdc)
{
	for (auto iter = _vItemSlot.begin(); iter != _vItemSlot.end(); ++iter)
	{
		iter->img->render(hdc, iter->x, iter->y);
	}
}
