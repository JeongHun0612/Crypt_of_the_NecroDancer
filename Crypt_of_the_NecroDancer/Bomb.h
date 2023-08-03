#pragma once
#include "Item.h"

class Bomb : public Item
{
private:
	int _count;
	int _power;
	FrameImage _effectImg;

	bool _isExplosion;

public:
	HRESULT init();
	HRESULT init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price);
	void release();
	void update();
	void render(HDC hdc);
	void render(HDC hdc, int beatCount);
	void slotRender(HDC hdc, Vec2_F pos);

	int getCount() { return _count; }
	void setCount(int count) { _count = count; }

	void setPosIdx(int idxX, int idxY) { _posIdx.x = idxX, _posIdx.y = idxY; }

	Bomb() {}
	~Bomb() {}
};

