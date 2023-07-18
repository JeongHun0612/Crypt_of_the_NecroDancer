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
	bool _isAttack;

public:
	HRESULT init(WEAPON_TYPE type);
	void release();
	void update();

	GImage* getImg() { return _img; }
	GImage* getEffectImg() { return _effectImg; }
	int getPower() { return _power; }


	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	bool getIsAttack() { return _isAttack; }

	Weapon() {}
	~Weapon() {}
};

