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
	FrameImage _effectImg;

	int _power;
	int _count;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void effectRender(HDC hdc);

	int getPower() { return _power; }

	Weapon() {}
	~Weapon() {}
};

