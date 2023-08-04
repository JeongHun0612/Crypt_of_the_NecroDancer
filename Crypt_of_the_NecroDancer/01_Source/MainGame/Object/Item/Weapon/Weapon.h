#pragma once
#include "Item.h"


class Weapon : public Item
{
private:
	FrameImage _effectImg;

	int _power;
	int _count;

public:
	HRESULT init();
	HRESULT init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price, int tileMaxCol);
	void release();
	void update();
	void render(HDC hdc);
	void slotRender(HDC hdc, Vec2_F pos);
	void effectRender(HDC hdc);

	int getPower() { return _power; }

	Weapon() {}
	~Weapon() {}
};

