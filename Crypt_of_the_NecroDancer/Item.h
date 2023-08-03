#pragma once

enum class ITEM_TYPE
{
	SHOVEL,
	WEAPON,
	ARMOR,
	BOMB,
	POTION
};

enum class WEAPON_TYPE
{
	DAGGER,
	BROADSWORD,
	BOW
};

enum class ARMOR_TYPE
{
	CLOTHES,
	LEATHER,
	CHAINMAIL,
	PLATE,
	HEAVY
};


class Item
{
protected:
	GImage* _slotImg;
	FrameImage _img;

	ITEM_TYPE _itemType;
	int _type;

	Vec2 _posIdx;
	float _posY;

	float _speed;

	int _price;
	int _distance;

	bool _isSale;
	bool _isCollider;
	bool _isChange;

public:
	virtual HRESULT init();
	virtual HRESULT init(int idxX, int idxY, ITEM_TYPE itemType, int type, int price);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void slotRender(HDC hdc, Vec2_F pos);

	Vec2 getPosIdx() { return _posIdx; }
	void setPosIdx(int idxX, int idxY) { _posIdx = { idxX, idxY }; }

	int getPrice() { return _price; }

	bool getIsSale() { return _isSale; }
	bool getIsCollider() { return _isCollider; }

	ITEM_TYPE getItemType() { return _itemType; }
	int getType() { return _type; }
	//WEAPON_TYPE getWeaponType() { return _weaponType; }
	//ARMOR_TYPE getArmorType() { return _armorType; }

	Item() {}
	~Item() {}
};

