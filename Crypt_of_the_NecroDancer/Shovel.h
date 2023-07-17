#pragma once
#include "Item.h"

class Shovel : public Item
{
private:
	GImage* _img;
	int _hardNess;
	bool _isDig;

public:
	HRESULT init();
	void release();
	void update();

	GImage* getImg() { return _img; }
	int getHardNess() { return _hardNess; }

	void setIsDig(bool isDig) { _isDig = isDig; }
	bool getIsDig() { return _isDig; }

	Shovel() {}
	~Shovel() {}
};

