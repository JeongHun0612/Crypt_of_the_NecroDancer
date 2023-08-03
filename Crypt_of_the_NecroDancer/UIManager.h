#pragma once
#include "SingletonBase.h"

//enum class INVENTORY_TYPE
//{
//	SHOVEL,
//	ATTACK,
//	BODY,
//
//	END
//};
//
//struct Inventory
//{
//	GImage* img;
//	INVENTORY_TYPE type;
//	int x, y;
//};

class Item;

enum class HEART_TYPE
{
	EMPTY,
	HALF,
	FULL
};


struct Coin
{
	GImage* img;
	int x, y;
	int coinCount;
};

struct Heart
{
	GImage* img;
	int x, y;
};

class UIManager : public SingletonBase<UIManager>
{
private:
	vector<Item*> _vEquipment;				// 소지 장비
	vector<Item*> _vExpendable;				// 소지 소모품

	vector<Heart> _vHeart;
	vector<Coin> _vCoin;

	int _prevHP;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addCoin(int idxX, int idxY, int coinCount);

	void addEquipment(Item* equipment);
	void deleteEquiment(Item* equipment);

	vector<Item*> getEquipment() { return _vEquipment; }
};

