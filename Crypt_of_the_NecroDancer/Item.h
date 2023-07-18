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
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	Item() {}
	~Item() {}
};

