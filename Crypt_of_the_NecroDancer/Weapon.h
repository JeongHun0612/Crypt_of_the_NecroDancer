#pragma once
#include "Item.h"

enum class WEAPON_TYPE
{
	DAGGER,
	BROADSWORD,
	RAPIER,
	SPEAR,

	END,
};

class Weapon : public Item
{
protected:
	GImage* _img;
	GImage* _effect;
	WEAPON_TYPE _type;
	int _power;

	vector<Weapon> _vWeapon;

public:
	HRESULT init(WEAPON_TYPE type);
	void release();
	void update();

	void attack();
	void changeWeapon(Weapon& weapon, WEAPON_TYPE type);

	GImage* getCurWeaponImg() { return _img; }

	Weapon() {}
	~Weapon() {}
};

