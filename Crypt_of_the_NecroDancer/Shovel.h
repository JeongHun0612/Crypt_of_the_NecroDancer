#pragma once
#include "Item.h"

class Shovel : public Item
{
private:
	GImage* _img;
	int _idxX;
	int _idxY;
	int _hardNess;

	vector<Shovel> _vShowShovel;
	float _destoryTime;


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	GImage* getImg() { return _img; }
	int getHardNess() { return _hardNess; }

	void addShowShovel(int idxX, int idxY);

	Shovel() {}
	~Shovel() {}
};

