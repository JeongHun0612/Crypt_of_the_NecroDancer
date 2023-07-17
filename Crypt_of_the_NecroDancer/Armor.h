#pragma once
#include "Item.h"

enum class ARMOR_TYPE
{
	CLOTHES,
	LEATHER,
	CHAINMAIL,
	PLATE,
	HEAVY
};

class Armor : public Item
{
private:
	GImage* _img;
	ARMOR_TYPE _type;
	int _defense;

public:
	HRESULT init();
	void release();
	void update();

	ARMOR_TYPE getArmorType() { return _type; }

	Armor() {}
	~Armor() {}
};

