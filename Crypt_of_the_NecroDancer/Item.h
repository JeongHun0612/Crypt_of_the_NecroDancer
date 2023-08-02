#pragma once

enum class ITEM_TYPE
{
	EQUIPMENT,
	EXPENDABLE,
};

enum class EQUIPMENT_TYPE
{
	SHOVEL,
	WEAPON,
	ARMOR
};

enum class EXPENDABLE_TYPE
{
	BOMB,
	POTION
};

class Item
{
protected:
	GImage* _slotImg;
	FrameImage _img;

	ITEM_TYPE _itemType;
	EQUIPMENT_TYPE _equipmentType;
	EXPENDABLE_TYPE _expendableType;

	Vec2 _posIdx;

public:
	virtual HRESULT init();
	virtual HRESULT init(int idxX, int idxY, int type);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render(HDC hdc, Vec2_F pos);

	ITEM_TYPE getItemType() { return _itemType; }
	EQUIPMENT_TYPE getEquipmentType() { return _equipmentType; }
	EXPENDABLE_TYPE getExpendableType() { return _expendableType; }

	Item() {}
	~Item() {}
};

