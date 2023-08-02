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
	ARMOR_TYPE _type;
	int _defense;

public:
	HRESULT init(int idxX, int idxY, int type);
	void release();
	void update();
	void render(HDC hdc);

	ARMOR_TYPE getArmorType() { return _type; }
	void setArmorType(ARMOR_TYPE type) { _type = type; }

	Armor() {}
	~Armor() {}
};

