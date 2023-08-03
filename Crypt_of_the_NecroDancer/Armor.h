#pragma once
#include "Item.h"

class Armor : public Item
{
private:
	int _defense;

public:
	HRESULT init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price);
	void release();
	void update();
	void render(HDC hdc);
	void slotRender(HDC hdc, Vec2_F pos);

	Armor() {}
	~Armor() {}
};

