#pragma once

enum class ITEM_TYPE
{
	SHOVEL,
	WEAPON,
	ARMOR,
	BOMB,
	POTION,

	END
};

class Item
{
public:
	HRESULT init();
	void release();
	void update();

	Item() {}
	~Item() {}
};

