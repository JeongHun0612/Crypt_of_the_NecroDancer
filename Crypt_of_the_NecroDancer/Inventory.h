#pragma once
#include "SingletonBase.h"

class Inventory : public SingletonBase<Inventory>
{
private:
	enum class ITEM_TYPE
	{
		SHOVEL,
		ATTACK,
		BODY,

		END
	};

	struct ItemSlot
	{
		GImage* img;
		ITEM_TYPE type;
		int x, y;
	};

	struct Item
	{
		GImage* img;
		ITEM_TYPE _itemType;
		int x, y;
	};

private:
	vector<ItemSlot> _vItemSlot;
	vector<Item> _vInventory;

public:
	HRESULT init(void);
	void release(void);
	void render(HDC hdc);

	Inventory() {}
	~Inventory() {}
};

