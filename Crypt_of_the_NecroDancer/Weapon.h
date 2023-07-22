#pragma once
#include "Item.h"

enum class WEAPON_TYPE
{
	DAGGER,
	BROADSWORD,
	RAPIER,
	SPEAR
};

class Weapon : public Item
{
private:
	GImage* _img;
	GImage* _effectImg;

	int _power;
	int _count;

public:
	HRESULT init(WEAPON_TYPE type);
	void release();
	void update();
	void render(HDC hdc);

	GImage* getImg() { return _img; }
	GImage* getEffectImg() { return _effectImg; }
	int getPower() { return _power; }

	Weapon() {}
	~Weapon() {}
};

