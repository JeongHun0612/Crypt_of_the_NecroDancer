#pragma once
#include "../Item.h"

class Shovel : public Item
{
private:
	int _hardNess;
	float _destoryTime;
	bool _isDestory;

public:
	HRESULT init();
	HRESULT init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price, int tileMaxCol);
	void release();
	void update();
	void render(HDC hdc);
	void effectRender(HDC hdc);
	void slotRender(HDC hdc, Vec2_F pos);

	int getHardNess() { return _hardNess; }
	bool getDestory() { return _isDestory; }

	Shovel() {}
	~Shovel() {}
};

